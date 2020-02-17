/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editors/Windows/EntityViewer.h>
#include <UWUEngine/Editors/Utils.h>
#include <UWUEngine/Systems/CompSpaceSys.h>
#include <UWUEngine/Systems/LogSys.h>

#include <magic_enum.hpp>
#include <imgui.h>

size_t currentSpaceID = 0;
std::string componentSpaceNames[]
{
  "GamePlay",
  "Environment",
  "UI",
  "Particle",
  "Light",
  "Debug"
};

using namespace UWUEngine;
using namespace Editors;

EntityID EntityViewer::selected{ 0 };
ISpace* EntityViewer::componentSpace{};

static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

EntityViewer::EntityViewer(ISpace* p) :
  Window(p,"Entity Viewer", true)
{
  auto& compSys = GetSystem<CompSpaceSys>();
  componentSpace = &compSys.space_gameplay;
}

EntityViewer::~EntityViewer() = default;

void EntityViewer::Setup()
{
}

void EntityViewer::Update()
{
  //Generate pop up window
  PopUpRightClick();

  //Select space;
  SpaceSelect();

  auto& entityComp = GetComponent<EntityComp>(componentSpace);
  auto& hierarchyComp = GetComponent<HierarchyComp>(componentSpace);
  //Iterate through EntityID container
  for (auto id : entityComp.GetIDs())
  {
    //If the current entity is a child, skip
    if (hierarchyComp.GetParent(id))
    {
      continue;
    }
    UpdateEntity(id);
  }
}

EntityID EntityViewer::GetSelectedEntity()
{
  return selected;
}

ISpace* EntityViewer::GetComponentSpace()
{
  return componentSpace;
}

void Editors::EntityViewer::SetSelectedEntity(EntityID ID)
{
  selected = ID;
}

void EntityViewer::UpdateEntity(EntityID id)
{
  auto& entityComp = GetComponent<EntityComp>(componentSpace);
  auto& hierarchyComp = GetComponent<HierarchyComp>(componentSpace);

  ImGuiTreeNodeFlags nodeFlags = baseFlags;
  const std::vector<EntityID>& children = hierarchyComp.GetChildren(id);

  //Get the name of the child, if there's no name get the type
  const std::string& name = entityComp.HasName(id) ?
    entityComp.GetName(id) :
    "Object";

  //Set Node Flags
  //If children is empty
  if (children.empty())
  {
    nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
  }
  //If current node is selected, highlight
  if (selected == id)
  {
    nodeFlags |= ImGuiTreeNodeFlags_Selected;
  }

  //Create node
  //If tree is open
  //Create the children tree
  if (ImGui::TreeNodeEx(name.c_str(), nodeFlags))
  {
    //Iterate through all children and update them
    for (auto child : children)
    {
      UpdateEntity(child);
    }
    //If a tree is updated instead of a leaf, pop tree
    if (!children.empty())
    {
      ImGui::TreePop();
    }
  }

  //Node Input
  //If the item is being clicked, it's selected
  if (ImGui::IsItemClicked() || ImGui::IsItemClicked(1))
  {
    selected = id;
  }
  if (ImGui::IsItemClicked(1))
  {
    ImGui::OpenPopup("Entity Ops");
  }
}

void EntityViewer::PopUpRightClick()
{
  auto& entitySys = GetSystem<EntitySys>();
  auto& logSys = GetSystem<LogSys>();
  if (ImGui::BeginPopupContextWindow("Entity Ops"))
  {
    if (ImGui::Button("New"))
    {
      entitySys.CreateEntity(componentSpace);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    HelpMarker("This is work in progress");
    if (ImGui::Button("Delete"))
    {
      entitySys.DestroyEntity(componentSpace, selected);
      ImGui::CloseCurrentPopup();
    }
    if (ImGui::Button("Delete All"))
    {
      logSys.Log(LogSys::WARNING) << "Destroy all is not implemented yet" << std::endl;
      //EntityManager::DestroyAll();
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

void EntityViewer::SpaceSelect() const
{
  if (ImGui::BeginCombo("Space", componentSpaceNames[currentSpaceID].c_str()))
  {
    for (int i = 0; i < IM_ARRAYSIZE(componentSpaceNames); i++)
    {
      bool isSelected = i == currentSpaceID;
      if (ImGui::Selectable(componentSpaceNames[i].c_str(), isSelected))
      {
        auto& compSys = GetSystem<CompSpaceSys>();
        currentSpaceID = i;
        selected = 0;
        //Select the correct space
        switch (i)
        {
        case  0:
          componentSpace = &compSys.space_gameplay;
          break;

        case  1:
          componentSpace = &compSys.space_environment;
          break;

        case  2:
          componentSpace = &compSys.space_ui;
          break;

        case  3:
          componentSpace = &compSys.space_particle;
          break;

        case  4:
          componentSpace = &compSys.space_light;
          break;

        case  5:
          componentSpace = &compSys.space_debug;
          break;
        default:;
        }
      }

    }
    ImGui::EndCombo();
  }
}
