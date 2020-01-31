#pragma once
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <map>
#include <assert.h>
#include <sstream>

//TODO: templatize an entity cache object specialized by the behaviors entity type with all the entity cache data plus behavior data
class BehaviorComponentManager;

class BaseBehavior
{
public:
  BaseBehavior(EntityID id);
  virtual ~BaseBehavior() = default;
  virtual void Update(){}
  virtual void Render();
  virtual void Serialize(std::ofstream& stream) {}
  virtual void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath){}
 // virtual void MakeImGUI(){}
  void SetID(EntityID id);
  EntityID GetID() const;
  void SetKey(std::string cachekey_) { cachekey = cachekey_; }
  std::string GetKey() { return cachekey; }
private:
  std::string cachekey;
  EntityID id_;
};

struct BaseCachedBehavior
{
  virtual void Deserialize(rapidjson::Value &object){}
  virtual void Instantiate(EntityID ID);
  virtual void InstantiateBehavior(EntityID id){} //TODO: set cachekey
  std::string filepath;
};

template <EntityManager::Type T>
struct CachedBehavior : public BaseCachedBehavior
{
  virtual void Deserialize(rapidjson::Value& object) {}
};



template <EntityManager::Type T>
class Behavior : public BaseBehavior
{
public:
  virtual void Update() {}
  virtual void Render() {}
  virtual void Serialize(std::ofstream& stream) {}
  virtual void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) {}
  //virtual void MakeImGUI();
  Behavior(EntityID id) : BaseBehavior(id){}
  ~Behavior() = default;
};

template<EntityManager::Type T>
static BaseBehavior* MakeBehavior(EntityID id)
{
  return static_cast<BaseBehavior*>(new Behavior<T>(id));
}

template<EntityManager::Type T>
static BaseCachedBehavior* MakeCachedBehavior()
{
  return static_cast<BaseCachedBehavior*>(new CachedBehavior<T>());
}

const std::map<EntityManager::Type, BaseBehavior * (* const)(EntityID)> allBehaviors =
{
  //whenever you make a specialization of a behavior, copy and paste another line below with the right type
{ EntityManager::Type::Text_,			      MakeBehavior<EntityManager::Type::Text_> },
{ EntityManager::Type::ParticleEmitter, MakeBehavior<EntityManager::Type::ParticleEmitter> },
{ EntityManager::Type::Particle,        MakeBehavior<EntityManager::Type::Particle> },
{ EntityManager::Type::Player,			    MakeBehavior<EntityManager::Type::Player>},
{ EntityManager::Type::Fang_,           MakeBehavior<EntityManager::Type::Fang_>},
{ EntityManager::Type::Perception,      MakeBehavior<EntityManager::Type::Perception>},
{ EntityManager::Type::HUDHealth,       MakeBehavior<EntityManager::Type::HUDHealth>},
{ EntityManager::Type::HUDEnergy,       MakeBehavior<EntityManager::Type::HUDEnergy>},
{ EntityManager::Type::CameraBounds,       MakeBehavior<EntityManager::Type::CameraBounds>}

};

const std::map<EntityManager::Type, BaseCachedBehavior* (*const)()> allCachedBehaviors =
{
  //whenever you make a specialization of a cached behavior, copy and paste another line below with the right type
{ EntityManager::Type::ParticleEmitter, MakeCachedBehavior<EntityManager::Type::ParticleEmitter> }
};


class BehaviorComponentManager : public BaseComponent<BehaviorComponentManager>
{
public:
  BehaviorComponentManager() = default;
  ~BehaviorComponentManager();

  void InitObject(EntityID ID) override;
  void ShutdownObject(EntityID ID) override;
  void Update() override;
  static BaseBehavior* GetBaseBehavior(EntityID ID);

  static BaseCachedBehavior* CreateCachedBehavior(EntityManager::Type type);

  template<EntityManager::Type T>
  static Behavior<T>* GetBehavior(EntityID ID)
  {
    return dynamic_cast<Behavior<T>*>(behaviors[ID]);
  }
private:
  static std::map<EntityID, BaseBehavior*> behaviors;
};

#include <UWUEngine/Behaviors/TextObject.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Behaviors/HUDBehaviors.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>