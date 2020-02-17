/******************************************************************************/
/*!
\par        Project Umbra
\file       ComponentViewer.cpp
\author     Yi Qian
\date       2019/12/29
\brief      Component viewer window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editors/Windows/ComponentViewer.h>
#include <UWUEngine/Editors/Windows/EntityViewer.h>
#include <UWUEngine/Editors/Utils.h>
#include <UWUEngine/Component/EntityComp.h>

//All the components
//#include <UWUEngine/Editors/Components/EditorTransform.h>
//#include <UWUEngine/Editors/Components/EditorPhysics.h>
//#include <UWUEngine/Editors/Components/EditorTexture.h>

#include <imgui.h>
#include <UWUEngine/Systems/EntitySys.h>
#include <magic_enum.hpp>

using namespace UWUEngine;
using namespace Editors;

#define REGISTER_COMPONENT(name) \
  std::shared_ptr<name> name ## _ = std::make_shared<name>(#name); \
  components.insert({ name ## _->GetName(), name ## _ }) \

ComponentViewer::ComponentViewer(ISpace* p) :
  Window(p,"Component Viewer", true)
{
  //Register all the components here
  //REGISTER_COMPONENT(Transform);
  //REGISTER_COMPONENT(Physics);
  //REGISTER_COMPONENT(Texture);
}

ComponentViewer::~ComponentViewer()
= default;

void ComponentViewer::Setup()
{

}

void ComponentViewer::Update()
{
  auto& entityComp = GetComponent<EntityComp>(EntityViewer::GetComponentSpace());
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
  if (!entityComp.HasName(selected))
  {
    //entityComp.SetName(selected, "Object");
  }
  //std::string& name = EntityViewer::name.find(selected)->second;

  //Display the current entity and name
  ImGui::Text("ID   : %d", selected);
  //InputText("Name", &name);
  ImGui::Separator();

  //Iterate through all components and get relative data
  for (const auto& component : components)
  {
    component.second->UpdateID(selected);
    //If the component is not active, skip
    if (!component.second->IsActive())
    {
      continue;
    }
    component.second->Render();
  }
}
