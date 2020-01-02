/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorTransform.cpp
\author     Yi Qian
\date       2019/12/31
\brief      Transform Editor

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/Components/EditorTransform.h>
#include <UWUEngine/Component/TransformComponentManager.h>

using namespace Editors;

Transform::Transform(std::string name):
Component(std::move(name))
{
}

void Transform::CheckActive(EntityID id)
{
  isActive = TransformComponentManager::IsActive(id);
}

void Transform::UpdateUI()
{
  translation.UpdateUI();
  rotation.UpdateUI();
  scale.UpdateUI();
}

void Transform::UpdateComponent(EntityID id)
{
  translation.UpdateElement(reinterpret_cast<glm::vec3*>(&TransformComponentManager::translation_[id]));
  rotation.UpdateElement(&TransformComponentManager::rotation_[id]);
  scale.UpdateElement(&TransformComponentManager::scale_[id]);
}
