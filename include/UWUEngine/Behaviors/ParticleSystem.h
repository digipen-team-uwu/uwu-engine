#pragma once
#include <memory>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Timer.h>
#include <glm/glm.hpp>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Component/ColliderComponentManager.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityCacher.h>

namespace psc = ParticleSystemConstants;

struct ParticleEvent
{
  struct Color
  {
    FlatOrRange<glm::vec4> color = glm::vec4{ 0, 0, 0, 0 };
    FlatOrRange<glm::vec4> endColor = psc::UNUSED_VEC4;
    FlatOrRange<float> colorRate = 1;
  }color;

  struct Size
  {
    FlatOrRange<glm::vec3> scale = glm::vec3{ 1, 1, 1 };
    FlatOrRange<glm::vec3> endScale = psc::UNUSED_VEC3;
    FlatOrRange<float> scaleRate = 1;
  }scale;


  FlatOrRange<float> rotationalVelocity =  0;
  
  FlatOrRange<float> startRotation = 0;

  FlatOrRange<float> emissionRate = 1;

  
    //all 3 indexes into the vector correspond to the same particle texture
  struct Sprite
  {
    std::vector<AnimationComponentManager::AnimationData> animations;
    std::vector<std::string> textures;
    std::vector<glm::uvec2> dimensions;
  }sprite;
  
  FlatOrRange<int> particlesPerEmission = 1;

  FlatOrRange<float> speed = 1.f;

    //rotation of velocity direction vector

  struct Direction
  {
    FlatOrRange<float> polarCoordsRotation = psc::UNUSED_FLOAT;
    FlatOrRange<glm::vec2> sphereCoordsRotation = psc::UNUSED_VEC2;
  }direction;

  FlatOrRange<glm::vec4> acceleration = glm::vec4{ 0, 0, 0, 0 };

  FlatOrRange<float> lifetime = psc::UNUSED_FLOAT;

  FlatOrRange<glm::vec4> posOffset = glm::vec4{ 0, 0, 0, 0 };

  FlatOrRange<float> inverseMass = 1.f;

 std::shared_ptr<std::vector<std::shared_ptr<Polynomial>>> vectorfieldx = NULL;

 std::shared_ptr<std::vector<std::shared_ptr<Polynomial>>> vectorfieldy = NULL;

  bool endWithAnimation = false;

  bool rotateByVelocity = false;

  bool UIParticles = false;

  float eventLength = psc::UNUSED_FLOAT;
};

template<>
class Behavior<EntityManager::Type::Particle> : public BaseBehavior
{
public:
  Behavior(EntityID id) : BaseBehavior(id) {}
  void Update();
  void InitData(ParticleEvent &partEvent);
  void OnCollide(CollisionInfo const& info);
private:
  float baseRotation{};
  float lifetime{};
  float maxLife{};
  glm::vec4 endColor{};
  glm::vec3 endScale{};
  std::shared_ptr<Polynomial> vectorfieldx;
  std::shared_ptr<Polynomial> vectorfieldy;
  float colorRate {};
  float scaleRate {};
  bool endWithAnimation = false;
  bool rotateByVelocity = false;
  bool UIParticle = false;
};

template<>
class Behavior<EntityManager::Type::ParticleEmitter> : public BaseBehavior
{
public:
  Behavior(EntityID id) : BaseBehavior(id){}
  void Update();
  void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath);
  void PushEvent(ParticleEvent partEvent);
  void PushEvents(const std::vector<ParticleEvent>& partEvent);
  ParticleEvent& GetEvent(int eventNumber = 0) { return particleEvents[eventNumber]; }
  //int GetCurrentEvent();
  //ParticleEvent &GetParticleEvent(int eventNumber);
private:
  Timer emissionTimer;
  std::vector<ParticleEvent> particleEvents;
  Timer eventTimer;
  int currentEvent = 0;
  std::string name;
};

template<>
class CachedBehavior<EntityManager::Type::ParticleEmitter> : public BaseCachedBehavior
{
  std::vector<ParticleEvent> particleEvents;
  void Deserialize(rapidjson::Value& object);
  void InstantiateBehavior(EntityID id);
};