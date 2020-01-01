/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorComponentViewer.cpp
\author     Yi Qian
\date       2019/12/29
\brief      Component viewer window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/Windows/EditorComponentViewer.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>

//All the components
#include <UWUEngine/Editor/Components/EditorTransform.h>

#include <imgui.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <magic_enum.hpp>

using namespace Editors;

#define REGISTER_COMPONENT(name) \
  std::shared_ptr<name> name ## _ = std::make_shared<name>(#name); \
  components.insert({ name ## _->GetName(), name ## _ }); \

ComponentViewer::ComponentViewer():
Window("ComponentViewer", true)
{
  //Register all the components here
  REGISTER_COMPONENT(Transform)
}

ComponentViewer::~ComponentViewer()
= default;

void ComponentViewer::Setup()
{
  //Get selected item id and name
  EntityID selected = EntityViewer::GetSelectedEntity();

  //If no entity selected, print message and quit
  if (!selected)
  {
    ImGui::Text("No Entity selected");
    return;
  }

  //If the entity doesn't have a name yet
  //Create a place holder with type name
  if (!EntityViewer::HasName(selected))
  {
    EntityViewer::SetName(selected, magic_enum::enum_name(EntityManager::GetType(selected)).data());
  }
  std::string& name = EntityViewer::name.find(selected)->second;

  //Display the current entity and name
  ImGui::Text("ID   : %d", selected);
  ImGui::InputText(
  "Name", name.data(), 50);
  ImGui::Separator();
}

void ComponentViewer::Update()
{
  //Get selected item id
  EntityID selected = EntityViewer::GetSelectedEntity();
  //If no entity selected, quit
  if (!selected)
  {
    return;
  }

  //Iterate through all components and get relative data
  for (auto component : components)
  {
    component.second->Render(selected);
  }
}
