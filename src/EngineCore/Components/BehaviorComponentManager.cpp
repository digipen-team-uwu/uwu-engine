/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       BehaviorComponentManager.cpp
  \author     Hadi Alhussieni
  \date       2019/10/06
  \brief      Implementation of object-specific behavior system for specialized
              private data and render/update procedures.

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Graphics/RenderSys.h>
#include <UWUEngine/Entity/EntityManager.h>

namespace UWUEngine
{
  BehaviorComp::~BehaviorComponentManager()
  {
    auto ids = EntityManager::GetIDs();
    auto it = ids.begin();
    while (it != ids.end())
    {
      if (IsActive(*it))
        delete behaviors[*it];
      it++;
    }
  }

  void BaseBehavior::Render()
  {
    //Render::DrawObject(id_);
  }

  void BaseBehavior::SetID(EntityID id)
  {
    id_ = id;
  }

  EntityID BaseBehavior::GetID() const
  {
    return id_;
  }


  void BehaviorComp::Update()
  {
    for (auto& it : behaviors)
    {
      it.second->Update();
    }
  }

  BaseBehavior::BaseBehavior(EntityID id) : id_(id)
  {
  }

  void BehaviorComp::InitObject(EntityID ID)
  {
    const auto funct = allBehaviors.find(EntityManager::GetType(ID));
    if (funct != allBehaviors.end())
    {
      behaviors[ID] = funct->second(ID);
    }
  }

  BaseCachedBehavior* BehaviorComp::CreateCachedBehavior(EntityManager::Type type)
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
    auto behavior = behaviors.find(ID);
    if (behavior != behaviors.end())
    {
      delete behaviors[ID];
      behaviors.erase(ID);
    }
  }

  BaseBehavior* BehaviorComp::GetBaseBehavior(EntityID ID)
  {
    return behaviors[ID];
  }

  void BaseCachedBehavior::Instantiate(EntityID ID)
  {
    //+2 because of the slash
    std::string key = filepath.substr(strlen(SerializationConstants::JSON_PATH) + 2 + magic_enum::enum_name(EntityManager::GetType(ID)).size());
    //strip .json
    key = key.substr(0, key.size() - 5);
    BehaviorComp::GetBaseBehavior(ID)->SetKey(key);
    InstantiateBehavior(ID);
  }
}
