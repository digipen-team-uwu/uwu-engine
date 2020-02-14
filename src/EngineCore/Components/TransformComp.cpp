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
#include <UWUEngine/Component/TransformComp.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <UWUEngine/constants.h>

//TODO: SetRelativeTransform for children

namespace UWUEngine
{

Transform::Transform(TransformComp& t, EntityID id) :
  Transform(t.rotation_[id], t.translation_[id], t.scale_[id]) {}

Transform::Transform(float& rotation, glm::vec4& translation, glm::vec3& scale) :
  rotation_(rotation), translation_(translation), scale_(scale) {}

Transform TransformComp::operator[](EntityID index)
{
  return Transform(rotation_[index], translation_[index], scale_[index]);
}

Transform TransformComp::getTransform(EntityID index)
{
  return Transform(rotation_[index], translation_[index], scale_[index]);
}

void TransformComp::InitObject(EntityID ID)
{
  translation_[ID] = { 0.f, 0.f, 0.f, 1.f };
  rotation_[ID] = 0.f;
  scale_[ID] = { 1.f, 1.f, 1.f };
}

glm::mat4 TransformComp::GetModelMatrix(EntityID ID)
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

glm::mat4 TransformComp::GetSpineModelMatrix(EntityID ID)
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

const glm::vec4& TransformComp::OffsetTranslation(EntityID ID, glm::vec3 const& offset)
{
  return translation_[ID] += glm::vec4{ offset, 0 };
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

const std::vector<glm::vec4>& TransformComp::GetArrayTranslation()
{
  return translation_;
}

const std::vector<glm::vec3>& TransformComp::GetArrayScale()
{
  return scale_;
}

const std::vector<float>& TransformComp::GetArrayRotation()
{
  return rotation_;
}
#pragma endregion

}