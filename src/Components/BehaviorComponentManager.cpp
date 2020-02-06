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
#include <UWUEngine/Graphics/Render.h>
#include <UWUEngine/Entity/EntityManager.h>

template<>
size_t RegisterComponentHelper<BehaviorComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<BehaviorComponentManager>(ComponentUpdateOrder::Behavior);

namespace goc = GameObjectConstants;

std::unordered_map<EntityID, BaseBehavior*> BehaviorComponentManager::behaviors;

BehaviorComponentManager::~BehaviorComponentManager()
{
  auto ids = EntityManager::GetIDs();
  auto it = ids.begin();
  while (it != ids.end())
  {
    if(IsActive(*it))
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


void BehaviorComponentManager::Update()
{
  for( auto & it : behaviors)
  {
      it.second->Update();
  }
}

BaseBehavior::BaseBehavior(EntityID id) : id_(id) 
{  
}

void BehaviorComponentManager::InitObject(EntityID ID)
{
    const auto funct = allBehaviors.find(EntityManager::GetType(ID));
    if(funct != allBehaviors.end())
    {
        behaviors[ID] = funct->second(ID);
    }
}

BaseCachedBehavior* BehaviorComponentManager::CreateCachedBehavior(EntityManager::Type type)
{
  const auto funct = allCachedBehaviors.find(type);
  if (funct != allCachedBehaviors.end())
  {
    return funct->second();
  }
  return nullptr;
}

void BehaviorComponentManager::ShutdownObject(EntityID ID)
{
  auto behavior = behaviors.find(ID);
  if (behavior != behaviors.end())
  {
    delete behaviors[ID];
    behaviors.erase(ID);
  }
}

BaseBehavior* BehaviorComponentManager::GetBaseBehavior(EntityID ID)
{
  return behaviors[ID];
}

void BaseCachedBehavior::Instantiate(EntityID ID)
{
                                                                              //+2 because of the slash
  std::string key = filepath.substr(strlen(SerializationConstants::JSON_PATH) + 2 + magic_enum::enum_name(EntityManager::GetType(ID)).size());
                    //strip .json
  key = key.substr(0, key.size() - 5);
  BehaviorComponentManager::GetBaseBehavior(ID)->SetKey(key);
  InstantiateBehavior(ID);
}

