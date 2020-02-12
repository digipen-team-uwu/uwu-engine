#pragma once
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Component/Component.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <unordered_map>
#include <cassert>
#include <sstream>

//TODO: templatize an entity cache object specialized by the behaviors entity type with all the entity cache data plus behavior data
class BehaviorComp;

namespace UWUEngine
{
  class BaseBehavior
  {
  public:
    BaseBehavior(EntityID id);
    virtual ~BaseBehavior() = default;
    virtual void Update() {}
    virtual void Render();
    virtual void Serialize(std::ofstream& stream) {}
    virtual void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) {}
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
    virtual void Deserialize(rapidjson::Value& object) {}
    virtual void Instantiate(EntityID ID);
    virtual void InstantiateBehavior(EntityID id) {} //TODO: set cachekey
    std::string filepath;
  };

  template <EntitySys::Tag T>
  struct CachedBehavior : public BaseCachedBehavior
  {
    virtual void Deserialize(rapidjson::Value& object) {}
  };




  template <EntitySys::Tag T>
  class Behavior : public BaseBehavior
  {
  public:
    virtual void Update() {}
    virtual void Render() {}
    virtual void Serialize(std::ofstream & stream) {}
    virtual void Deserialize(rapidjson::Value & object, EntityID ID, const char* filePath) {}
    //virtual void MakeImGUI();
    Behavior(EntityID id) : BaseBehavior(id) {}
    ~Behavior() = default;
  };

  template<EntitySys::Tag T>
  static BaseBehavior* MakeBehavior(EntityID id)
  {
    return static_cast<BaseBehavior*>(new Behavior<T>(id));
  }

  template<EntitySys::Tag T>
  static BaseCachedBehavior* MakeCachedBehavior()
  {
    return static_cast<BaseCachedBehavior*>(new CachedBehavior<T>());
  }

  const std::map<EntitySys::Tag, BaseBehavior* (*const)(EntityID)> allBehaviors =
  {
    //whenever you make a specialization of a behavior, copy and paste another line below with the right type
  { EntitySys::Tag::Text_,			     MakeBehavior<EntitySys::Tag::Text_> },
  { EntitySys::Tag::ParticleEmitter, MakeBehavior<EntitySys::Tag::ParticleEmitter> },
  { EntitySys::Tag::Particle,        MakeBehavior<EntitySys::Tag::Particle> },
  { EntitySys::Tag::Player,			     MakeBehavior<EntitySys::Tag::Player>},
  { EntitySys::Tag::Fang_,           MakeBehavior<EntitySys::Tag::Fang_>},
  { EntitySys::Tag::Perception,      MakeBehavior<EntitySys::Tag::Perception>},
  { EntitySys::Tag::HUDHealth,       MakeBehavior<EntitySys::Tag::HUDHealth>},
  { EntitySys::Tag::HUDEnergy,       MakeBehavior<EntitySys::Tag::HUDEnergy>},
  { EntitySys::Tag::CameraBounds,    MakeBehavior<EntitySys::Tag::CameraBounds>}

  };

  const std::map<EntitySys::Tag, BaseCachedBehavior* (*const)()> allCachedBehaviors =
  {
    //whenever you make a specialization of a cached behavior, copy and paste another line below with the right type
  { EntitySys::Tag::ParticleEmitter, MakeCachedBehavior<EntitySys::Tag::ParticleEmitter> }
  };



  class BehaviorComp : public Component<BehaviorComp, BaseBehavior>
  {
  public:
    BehaviorComp() = default;
    ~BehaviorComp();

    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;
    void Update() override;
    static BaseBehavior* GetBaseBehavior(EntityID ID);

    static BaseCachedBehavior* CreateCachedBehavior(EntitySys::Tag type);

    template<EntitySys::Tag T>
    static Behavior<T>* GetBehavior(EntityID ID)
    {
      return dynamic_cast<Behavior<T>*>(behaviors[ID]);
    }
  private:
    static std::unordered_map<EntityID, BaseBehavior*> behaviors;
  };
}

#include <UWUEngine/Behaviors/TextObject.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Behaviors/HUDBehaviors.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>