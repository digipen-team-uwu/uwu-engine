#pragma once
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/Component.h>
#include <unordered_map>
#include <cassert>
#include <sstream>
#include "UWUEngine/Systems/EntitySys.h"

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
    // virtual void MakeImGUI(){}
    void SetID(EntityID id);
    EntityID GetID() const;
    void SetKey(std::string &&cachekey_) { cachekey = std::move(cachekey_); }
    std::string GetKey() { return cachekey; }
    EntityComp::Tag GetTag() { return tag; };
    void SetTag(EntityComp::Tag tag_) { tag = tag_; }
  private:
    std::string cachekey;
    EntityID id_;
    EntityComp::Tag tag;
  };

  struct BaseCachedBehavior
  {
    //virtual void Deserialize(rapidjson::Value& object) {}
    virtual void Instantiate(EntityID ID);
    virtual void InstantiateBehavior(EntityID id) {} //TODO: set cachekey
    std::string filepath;
  };

  template <EntityComp::Tag T>
  struct CachedBehavior : public BaseCachedBehavior
  {
    //virtual void Deserialize(rapidjson::Value& object) {}
  };




  template <EntityComp::Tag T>
  class Behavior : public BaseBehavior
  {
  public:
    virtual void Update() {}
    //virtual void MakeImGUI();
    Behavior(EntityID id) : BaseBehavior(id) { SetTag(T); }
    ~Behavior() = default;
  };

  template<EntityComp::Tag T>
  static BaseBehavior* MakeBehavior(EntityID id)
  {
    return static_cast<BaseBehavior*>(new Behavior<T>(id));
  }

  template<EntityComp::Tag T>
  static BaseCachedBehavior* MakeCachedBehavior()
  {
    return static_cast<BaseCachedBehavior*>(new CachedBehavior<T>());
  }

  const std::map<EntityComp::Tag, BaseBehavior* (*const)(EntityID)> allBehaviors =
  {
    //whenever you make a specialization of a behavior, copy and paste another line below with the right type
  { EntityComp::Tag::FALLS, MakeBehavior<EntityComp::Tag::FALLS> },

  };

  const std::map<EntityComp::Tag, BaseCachedBehavior* (*const)()> allCachedBehaviors =
  {
    //whenever you make a specialization of a cached behavior, copy and paste another line below with the right type
  { EntityComp::Tag::FALLS, MakeCachedBehavior<EntityComp::Tag::FALLS> }
  };;

  class BehaviorComp : public Component<BehaviorComp, BaseBehavior>
  {
  public:
    BehaviorComp(ISpace *space) : Component(space){}
    ~BehaviorComp();

    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;
 
    auto GetBaseBehaviors(EntityID ID);

    BaseCachedBehavior* CreateCachedBehavior(EntityComp::Tag type);

    template<EntityComp::Tag T>
    Behavior<T>* GetBehavior(EntityID ID)
    {
      const auto behavior = behaviors.equal_range(ID);
      for (auto it = behavior.first; it != behavior.second; ++it)
      {
        if(it->second->GetTag() == T)
        {
          return dynamic_cast<Behavior<T>*>(behaviors[ID]);
        }
      }
      return nullptr;
    }
    friend class BehaviorSys;
  private:
    std::unordered_multimap<EntityID, BaseBehavior*> behaviors;
  };
}

/*
#include <UWUEngine/Behaviors/TextObject.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Behaviors/HUDBehaviors.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>
*/