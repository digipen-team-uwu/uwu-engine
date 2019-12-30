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
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>

#include <magic_enum.hpp>
#include <imgui.h>

EntityID EditorEntityViewer::selected{0};
std::unordered_map<EntityID, std::string> EditorEntityViewer::name;
static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

EditorEntityViewer::EditorEntityViewer():
EditorWindow("EntityViewer")
{
}

EditorEntityViewer::~EditorEntityViewer() = default;

void EditorEntityViewer::Setup()
{
}

void EditorEntityViewer::Update()
{
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

EntityID EditorEntityViewer::GetSelectedEntity()
{
  return selected;
}

void EditorEntityViewer::SetName(EntityID ID, std::string name_)
{
  name[ID] = name_;
}

std::string EditorEntityViewer::GetName(EntityID ID)
{
  return name[ID];
}

bool EditorEntityViewer::HasName(EntityID ID)
{
  auto name_ = name.find(ID);
  return name_ != name.end();
}

void EditorEntityViewer::UpdateEntity(EntityID id)
{
  ImGuiTreeNodeFlags nodeFlags = baseFlags;
  const std::vector<EntityID>& children = ParentChildComponentManager::GetChildren(id);

  //Get the name of the child, if there's no name get the type
  std::string name = HasName(id) ? 
  GetName(id) :
  magic_enum::enum_name(EntityManager::GetType(id)).data();

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
  //If the item is being clicked, it's selected
  if (ImGui::IsItemClicked())
  {
    selected = id;
  }
}
