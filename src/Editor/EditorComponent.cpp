/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorComponent.cpp
\author     Yi Qian
\date       2019/12/31
\brief      Component viewer window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/EditorComponent.h>
#include "UWUEngine/Helper.h"
#include <glm/glm.hpp>
#include <imgui.h>

using namespace Editors;

#pragma region ELEMENT_SPECIALIZATION



template <>
void Element<float>::UpdateUI()
{
  ImGui::DragFloat(label.c_str(), element);
}

template <>
void Element<int>::UpdateUI()
{
  ImGui::DragInt(label.c_str(), element);
}

template <>
void Element<glm::vec2>::UpdateUI()
{
  ImGui::DragFloat2(label.c_str(), &element->x);
}

template <>
void Element<glm::vec3>::UpdateUI()
{
  ImGui::DragFloat3(label.c_str(), &element->x);
}

template <>
void Element<glm::vec4>::UpdateUI()
{
  ImGui::DragFloat4(label.c_str(), &element->x);
}

template <>
void Element<std::string>::UpdateUI()
{
  ImGui::InputText(label.c_str(), element->data(), 50);
}

#pragma endregion

const std::string& Component::GetName() const
{
  return name;
}

void Component::Render()
{
  //Render component header
  if (ImGui::CollapsingHeader(name.c_str()))
  {
    UpdateUI();
  }

  ImGui::Separator();
}

void Component::UpdateID(EntityID id)
{
  //If new id is the same as the old one, skip
  if (id == current)
  {
    return;
  }
  current = id;

  CheckActive(current);
  if (isActive)
  {
    UpdateComponent(current);
  }
}

bool Component::IsActive() const
{
  return isActive;
}
