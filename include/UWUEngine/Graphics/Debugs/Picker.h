#pragma once
#include <unordered_map>
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/System.h>

using Point = glm::vec2;

namespace UWUEngine
{

class Picker : public System
{
public:

  struct AABB
  {
    AABB(float w_, float h_, Point bot_left) : w(w_), h(h_), bottom_left(bot_left) {}
    float w;
    float h;
    Point bottom_left;
  };

  enum class state
  {
    PICK,
    RELEASE,

    Total
  };

  Picker(ISpace*);
  ~Picker() = default;
  void Update() override;
  void Pick();
  void PickID();
  glm::vec2 GetMouseWorld();
  void CalculateMouseWorld(glm::vec2 Pos);
  void Attaching(EntityID ID);
  void Detaching();
private:
  void Reset();
  bool IsPointInAABB(AABB aabb, Point p);
  glm::mat3 GLFW_to_vp;
  glm::mat3 ndc_to_vp;
  glm::mat3 ndc_to_vf;
  glm::vec3 mouse_world;
  EntityID saved_ID;
  float saved_d;
  std::unordered_map<EntityID, float> ID_and_distance;
};

}
