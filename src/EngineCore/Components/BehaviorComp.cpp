/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       BehaviorComp.cpp
  \author     Hadi Alhussieni
  \date       2019/10/06
  \brief      Implementation of object-specific behavior system for specialized
              private data and render/update procedures.

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/EntityComp.h>

namespace UWUEngine
{
  BehaviorComp::~BehaviorComp()
  {
    for(auto it : Get<EntityComp>().GetIDs())
    {
      for(auto &jt : behaviors)
      {
        delete jt.second;
      }
    }
  }


  void BaseBehavior::SetID(EntityID id)
  {
    id_ = id;
  }

  EntityID BaseBehavior::GetID() const
  {
    return id_;
  }

  BaseBehavior::BaseBehavior(EntityID id) : id_(id)
  {
  }

  void BehaviorComp::InitObject(EntityID ID)
  {
    //const auto funct = allBehaviors.find(Get<EntityComp>().GetTags(ID));
    //if (funct != allBehaviors.end())
    //{
      //behaviors[ID] = funct->second(ID);
    //}
  }

  BaseCachedBehavior* BehaviorComp::CreateCachedBehavior(EntityComp::Tag type)
  {
    const auto funct = allCachedBehaviors.find(type);
    if (funct != allCachedBehaviors.end())
    {
      return funct->second();
    }
    return nullptr;
  }

  void BehaviorComp::ShutdownObject(EntityID ID)
  {
    const auto behavior = behaviors.equal_range(ID);
    for(auto it = behavior.first; it != behavior.second; ++it)
    {
      delete it->second;
      behaviors.erase(it);
    }
  }

  auto BehaviorComp::GetBaseBehaviors(EntityID ID)
  {
    return behaviors.equal_range(ID);
  }

  void BaseCachedBehavior::Instantiate(EntityID ID)
  {
    //+2 because of the slash
    //std::string key = filepath.substr(strlen(SerializationConstants::JSON_PATH) + 2 + magic_enum::enum_name(Get<EntitySys>().GetType(ID)).size());
    //strip .json
    //key = key.substr(0, key.size() - 5);
    //BehaviorComp::GetBaseBehavior(ID)->SetKey(key);
    //InstantiateBehavior(ID);
  }
}
