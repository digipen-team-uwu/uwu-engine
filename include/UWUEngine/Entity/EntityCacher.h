#pragma once
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/System.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <vector>
#include <array>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Physics/Colliders/Collider.h>
#include <rapidjson/document.h>


namespace UWUEngine
{

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
    std::array<::std::string, goc::MAX_SPRITES> filepaths;
  }texture;

  struct
  {
    bool active = false;
    ::std::string name;
    ::std::string json;
    ::std::string atlas;
    ::std::string skin;
    ::std::string defualtAnim;
    float scaleOffset;
  }spineSkeleton;

};

class EntityCacher : public System
{
public:
  EntityCacher();
  void CacheEntity(const CachedEntity& entity);
  void CacheBehavior(::std::string filepath, BaseCachedBehavior* behavior);
  bool EntityIsCached(EntityManager::Type type);
  EntityID CreateCachedEntity(const CachedEntity& entity);
  const CachedEntity& GetCachedEntity(EntityManager::Type type);
  void Update() override {}
  void CacheFile(::std::string file);
  void InstantiateCachedBehavior(EntityID id, ::std::string fileName);
  const ::std::vector<::std::string>& GetCachedFilepaths();
  void UpdateCachedBehavior(::std::string filename);
private:
  void MakeJsonObject(const char* filepath, rapidjson::Document& obj);
  ::std::unordered_map<EntityManager::Type, CachedEntity> entities;
  ::std::unordered_map<::std::string, BaseCachedBehavior*> behaviors;
  ::std::vector<::std::string> cachedFilepaths;
};

}
