#pragma once
#include <UWUEngine/System.h>
#include <glm/glm.hpp>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <vector>
#include <iostream>

namespace UWUEngine
{

template<>
class Behavior<EntitySys::Type::CameraBounds> : public BaseBehavior
{
public:
  Behavior(EntityID id);
  ~Behavior();
  //check if a position is within the bounding box.
  bool InBounds(glm::vec2 pos);
  //find closest point on box to pos via raycasting
  glm::vec2 GetClosestPoint(glm::vec2 pos, glm::vec2 direction);
  void Serialize(::std::ofstream& stream);
private:

};

class DynamicCamera : public System
{
public:
  DynamicCamera(ISpace*);
  void Update() override;
  static void Activate();
  static void Deactivate();
  static void SetTrackingSpeed(float speed);
  static void SetTrackingPos(const glm::vec4& pos);
  static void SetInnerBounds(float width_, float height_, glm::vec2 offset = { 0, 0 });
  static void AddBoundsObject(EntityID bounds);
  static void RemoveBoundsObject(EntityID bounds);
  static bool InAnyBounds(glm::vec2 pos);
  static glm::vec2 GetClosestPointOnBounds(glm::vec2 pos, glm::vec2 direction);
private:
  static bool IsActive;
  static glm::vec4 position;
  static float followSpeed;
  static float inwidth;
  static float inheight;
  static glm::vec2 inoffset;
  static ::std::vector<EntityID> bounds;
};

}
