#pragma once
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/BaseSystem.h>
#include "EntityManager.h"
#include <vector>
#include <array>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Physics/Colliders/Collider.h>


struct BaseCachedBehavior;

struct CachedEntity
{
  EntityManager::Type type;

  struct
  {
    bool active = false;
    glm::vec4 translation;
    float rotation;
    glm::vec3 scale;
  }transform;

  struct
  {
    bool active = false;
    PhysicsComponentManager::BodyType type;
    glm::vec4 velocity;
    glm::vec4 acceleration;
    glm::vec4 drag;
    float rotationalVelocity;
    float inverseMass;
  }physics;

  struct
  {
    bool active = false;
    std::array<AnimationComponentManager::AnimationData, goc::MAX_SPRITES> animations;
  }animation;

  struct
  {
    bool active = false;
    Collider::ShapeType type;
	Collider* collider;
  }collider;

  struct
  {
    bool active = false;
    std::array<std::string, goc::MAX_SPRITES> filepaths;
  }texture;

  struct
  {
    bool active = false;
    std::string name;
    std::string json;
    std::string atlas;
    std::string skin;
    std::string defualtAnim;
    float scaleOffset;
  }spineSkeleton;
  
};

class EntityCacher : public BaseSystem<EntityCacher>
{
public:
  EntityCacher();
  static void CacheEntity(const CachedEntity& entity);
  static void CacheBehavior(std::string filepath, BaseCachedBehavior *behavior);
  static bool EntityIsCached(EntityManager::Type type);
  static EntityID CreateCachedEntity(const CachedEntity& entity);
  static const CachedEntity& GetCachedEntity(EntityManager::Type type);
  void Update() override {}
  static void CacheFile(std::string file);
  static void InstantiateCachedBehavior(EntityID id, std::string fileName);
  static const std::vector<std::string>& GetCachedFilepaths();
  static void UpdateCachedBehavior(std::string filename);
private:
  static void MakeJsonObject(const char* filepath, rapidjson::Document& obj);
  static std::unordered_map<EntityManager::Type, CachedEntity> entities;
  static std::unordered_map<std::string, BaseCachedBehavior*> behaviors;
  static std::vector<std::string> cachedFilepaths;
};
