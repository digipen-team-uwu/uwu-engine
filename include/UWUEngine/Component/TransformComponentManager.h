/******************************************************************************/
/*!
\par        Project Umbra
\file       TransformComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing transform components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>

//Forward Declaration
namespace Editors
{
  class Transform;
}

class Transform
{
public:
  Transform(float& rotation, glm::vec4& translation, glm::vec3& scale) : rotation_(rotation), translation_(translation), scale_(scale) {}

#pragma region Setter
  void SetTranslation(const glm::vec4& translation);
  void SetScale(const glm::vec3& scale);
  void SetRotation(const float& rotation);
#pragma endregion

#pragma region Getter
  const glm::vec4 GetTranslation() const;
  const glm::vec3 GetScale() const;
  const float GetRotation() const;
#pragma endregion 

private:
  float& rotation_;
  glm::vec4& translation_;
  glm::vec3& scale_;
};

class TransformComponentManager : public BaseComponent<TransformComponentManager>
{
public:
  TransformComponentManager() = default;
  ~TransformComponentManager() = default;
  void Update() override {}
  void ShutdownObject(EntityID ID) override {}
  void InitObject(EntityID ID) override;

  Transform operator[](EntityID index);

  Transform getTransform(EntityID index);

#pragma region Getter
  const std::vector<glm::vec4>& GetArrayTranslation();
  const std::vector<float>& GetArrayRotation();
  const std::vector<glm::vec3>& GetArrayScale();
#pragma endregion 

  void Serialize(std::ofstream& stream, EntityID id);
  glm::mat4 GetModelMatrix(EntityID ID);
  glm::mat4 GetSpineModelMatrix(EntityID ID);
  const glm::vec4& OffsetTranslation(EntityID ID, glm::vec3 const& offset);

private:
  EntityVector<float> rotation_;
  EntityVector<glm::vec4> translation_;
  EntityVector<glm::vec3> scale_;

  // don't know who added
  friend class Editors::Transform;
};

//class TransformComponentManager : public BaseComponent<TransformComponentManager>
//{
//public:
//  TransformComponentManager() = default;
//  ~TransformComponentManager() = default;
//  void Update() override {};
//  void InitObject(EntityID ID) override;
//  void ShutdownObject(EntityID ID) override {};
//
//  static void SetTranslation(const glm::vec4& translation, EntityID ID);
//  static void SetRotation(float rotation, EntityID ID);
//  static void SetScale(const glm::vec3& scale, EntityID ID);
//
//  static const glm::vec3& GetScale(EntityID ID);
//  static const glm::vec4& GetTranslation(EntityID ID);
//  static float GetRotation(EntityID ID);
//
//  static const std::vector<glm::vec4>& GetArrayTranslation();
//  static const std::vector<float>& GetArrayRotation();
//  static const std::vector<glm::vec3>& GetArrayScale();
//
//  static glm::mat4 GetModelMatrix(EntityID ID);
//
//  static glm::mat4 GetSpineModelMatrix(EntityID ID);
//
//  static const glm::vec4& OffsetTranslation(EntityID ID, glm::vec3 const& offset);
//
//  friend void PhysicsComponentManager::Update();
//
//  // Prints all values of the given object to the given stream
//  // in JSON format, if the transform is activated for the object
//  static void Serialize(std::ofstream& stream, EntityID id);
//private:
//  static EntityVector<glm::vec4> translation_;
//  static EntityVector<float> rotation_;
//  static EntityVector<glm::vec3> scale_;
//
//  friend class Editors::Transform;
//};
