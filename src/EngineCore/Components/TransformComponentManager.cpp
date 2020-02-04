/******************************************************************************/
/*!
\par        Project Umbra
\file       TransformComponentManager.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing transform components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Component/TransformComponentManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/Serialization.h>

using namespace UWUEngine;

template<>
size_t RegisterComponentHelper<TransformComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<TransformComponentManager>(ComponentUpdateOrder::LAST);

//TODO: SetRelativeTransform for children

Transform TransformComponentManager::operator[](EntityID index)
{
  return Transform(rotation_[index], translation_[index], scale_[index]);
}

Transform TransformComponentManager::getTransform(EntityID index)
{
  return Transform(rotation_[index], translation_[index], scale_[index]);
}

void TransformComponentManager::InitObject(EntityID ID)
{
  translation_[ID] = { 0.f, 0.f, 0.f, 1.f };
  rotation_[ID] = 0.f;
  scale_[ID] = { 1.f, 1.f, 1.f };
}

glm::mat4 TransformComponentManager::GetModelMatrix(EntityID ID)
{
  Transform transform = getTransform(ID);
  glm::vec3 translation = transform.GetTranslation();
  glm::vec3 scale = transform.GetScale();
  float rotation = transform.GetRotation();
  return
    glm::translate(translation) *
    glm::rotate(rotation, glm::vec3(0, 0, 1)) *
    glm::scale(scale);
}

glm::mat4 TransformComponentManager::GetSpineModelMatrix(EntityID ID)
{
  Transform transform = getTransform(ID);
  glm::vec3 translation = transform.GetTranslation();
  glm::vec3 scale = transform.GetScale();
  float rotation = transform.GetRotation();
  translation.y -= scale.y / 2;
  return
    glm::translate(translation) *
    glm::rotate(rotation, glm::vec3(0, 0, 1)) *
    glm::scale(scale);
}

const glm::vec4& TransformComponentManager::OffsetTranslation(EntityID ID, glm::vec3 const& offset)
{
  return translation_[ID] += glm::vec4{ offset, 0 };
}

// The below code is written by Michael Rollosson Halbhuber
void TransformComponentManager::Serialize(std::ofstream& stream, EntityID id)
{
  // Check to see if the given object has a transform component
  if (IsActive(id))
  {
    // Open a "transform" JSON object
    stream << "\"transform\" :\n";
    stream << Tabs::TWO << "{\n";

    // Print the translation
    SerializeVec4(stream, "translation", translation_[id]);
    stream << ",\n";

    // Print the rotation
    stream << Tabs::THREE << "\"rotation\" : " << rotation_[id] << ",\n";

    // Print the scale
    SerializeVec3(stream, "scale", scale_[id]);
    stream << "\n";

    // Close the transform object
    stream << Tabs::TWO << "}";
  }
}

#pragma region Setter
void Transform::SetTranslation(const glm::vec4& translation)
{
  translation_ = translation;
}

void Transform::SetScale(const glm::vec3& scale)
{
  scale_ = scale;
}

void Transform::SetRotation(const float& rotation)
{
  rotation_ = rotation;
}
#pragma endregion

#pragma region Getter
const glm::vec4& Transform::GetTranslation() const
{
  return translation_;
}

const glm::vec3& Transform::GetScale() const
{
  return scale_;
}

const float& Transform::GetRotation() const
{
  return rotation_;
}

const std::vector<glm::vec4>& TransformComponentManager::GetArrayTranslation()
{
  return translation_;
}

const std::vector<glm::vec3>& TransformComponentManager::GetArrayScale()
{
  return scale_;
}

const std::vector<float>& TransformComponentManager::GetArrayRotation()
{
  return rotation_;
}
#pragma endregion
