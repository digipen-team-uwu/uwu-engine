#pragma once
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/Component.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <map>
#include <assert.h>
#include <sstream>

namespace  UWUEngine
{
  //TODO: templatize an entity cache object specialized by the behaviors entity type with all the entity cache data plus behavior data
  class BehaviorComp;

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

  template <EntitySys::Type T>
  struct CachedBehavior : public BaseCachedBehavior
  {
    virtual void Deserialize(rapidjson::Value& object) {}
  };



  template <EntitySys::Type T>
  class Behavior : public BaseBehavior
  {
  public:
    virtual void Update() {}
    virtual void Render() {}
    virtual void Serialize(std::ofstream& stream) {}
    virtual void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath) {}
    //virtual void MakeImGUI();
    Behavior(EntityID id) : BaseBehavior(id) {}
    ~Behavior() = default;
  };

  template<EntitySys::Type T>
  BaseBehavior* MakeBehavior(EntityID id)
  {
    return static_cast<BaseBehavior*>(new Behavior<T>(id));
  }

  template<EntitySys::Type T>
  BaseCachedBehavior* MakeCachedBehavior()
  {
    return static_cast<BaseCachedBehavior*>(new CachedBehavior<T>());
  }

  const std::map<EntitySys::Type, BaseBehavior * (* const)(EntityID)> allBehaviors =
  {
    //whenever you make a specialization of a behavior, copy and paste another line below with the right type
  { EntitySys::Type::Text_,			      MakeBehavior<EntitySys::Type::Text_> },
  { EntitySys::Type::ParticleEmitter, MakeBehavior<EntitySys::Type::ParticleEmitter> },
  { EntitySys::Type::Particle,        MakeBehavior<EntitySys::Type::Particle> },
  { EntitySys::Type::Player,			    MakeBehavior<EntitySys::Type::Player>},
  { EntitySys::Type::Fang_,           MakeBehavior<EntitySys::Type::Fang_>},
  { EntitySys::Type::Perception,      MakeBehavior<EntitySys::Type::Perception>},
  { EntitySys::Type::HUDHealth,       MakeBehavior<EntitySys::Type::HUDHealth>},
  { EntitySys::Type::HUDEnergy,       MakeBehavior<EntitySys::Type::HUDEnergy>},
  { EntitySys::Type::CameraBounds,       MakeBehavior<EntitySys::Type::CameraBounds>}

  };

  const std::map<EntitySys::Type, BaseCachedBehavior * (* const)()> allCachedBehaviors =
  {
    //whenever you make a specialization of a cached behavior, copy and paste another line below with the right type
  { EntitySys::Type::ParticleEmitter, MakeCachedBehavior<EntitySys::Type::ParticleEmitter> }
  };


  class BehaviorComp : public Component<BehaviorComp, BaseBehavior>
  {
  public:
    BehaviorComp() = default;
    ~BehaviorComp();

    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;
    void Update() override;
    BaseBehavior* GetBaseBehavior(EntityID ID);

    BaseCachedBehavior* CreateCachedBehavior(EntitySys::Type type);

    template<EntitySys::Type T>
    Behavior<T>* GetBehavior(EntityID ID)
    {
      return dynamic_cast<Behavior<T>*>(behaviors[ID]);
    }
  private:
    std::map<EntityID, BaseBehavior*> behaviors;
  };

#include <UWUEngine/Behaviors/TextObject.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Behaviors/HUDBehaviors.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>
}