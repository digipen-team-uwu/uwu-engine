/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Editor/EditorHelper.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>

#include <magic_enum.hpp>
#include <imgui.h>

using namespace Editors;

EntityID EntityViewer::selected{0};
std::unordered_map<EntityID, std::string> EntityViewer::name;
static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

EntityViewer::EntityViewer():
Window("Entity Viewer", true)
{
}

EntityViewer::~EntityViewer() = default;

void EntityViewer::Setup()
{
}

void EntityViewer::Update()
{
  //Generate pop up window
  PopUpRightClick();

  //Iterate through EntityID container
  for (auto id : EntityManager::GetIDs())
  {
    //If the current entity is a child, skip
    if (ParentChildComponentManager::GetParent(id))
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

void EntityViewer::SetName(EntityID ID, std::string name_)
{
  name[ID] = name_;
}

std::string EntityViewer::GetName(EntityID ID)
{
  return name[ID];
}

void EntityViewer::RemoveName(EntityID ID)
{
  name.erase(ID);
}

void EntityViewer::RemoveAllNames()
{
  name.clear();
}

bool EntityViewer::HasName(EntityID ID)
{
  auto name_ = name.find(ID);
  return name_ != name.end();
}

void EntityViewer::UpdateEntity(EntityID id)
{
  ImGuiTreeNodeFlags nodeFlags = baseFlags;
  const std::vector<EntityID>& children = ParentChildComponentManager::GetChildren(id);

  //Get the name of the child, if there's no name get the type
  const std::string& name = HasName(id) ? 
  GetName(id) :
  magic_enum::enum_name(EntityManager::GetType(id)).data();

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
  if (ImGui::BeginPopupContextWindow("Entity Ops"))
  {
    if (ImGui::Button("New"))
    {
      //TODO::Create new entity
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    HelpMarker("This is work in progress");
    if (ImGui::Button("Delete"))
    {
      EntityManager::Destroy(selected);
      ImGui::CloseCurrentPopup();
    }
    if (ImGui::Button("Delete All"))
    {
      EntityManager::DestroyAll();
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}
