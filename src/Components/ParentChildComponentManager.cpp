/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       ParentChildComponentManager.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for a hierarchal component

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Component/ParentChildComponentManager.h>

template<>
size_t RegisterComponentHelper<ParentChildComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<ParentChildComponentManager>(ComponentUpdateOrder::LAST);

std::unordered_map<EntityID, std::vector<EntityID>> ParentChildComponentManager::children;

EntityVector<EntityID> ParentChildComponentManager::parents(goc::INITIAL_OBJECT_COUNT);

const std::vector<EntityID>& ParentChildComponentManager::GetChildren(EntityID id)
{
  return children[id];
}

EntityID ParentChildComponentManager::GetParent(EntityID id)
{
  return parents[id];
}

void ParentChildComponentManager::AddChild(EntityID parent, EntityID child)
{
 children[parent].push_back(child);
  ParentChildComponentManager::Activate(child);
  parents[child] = parent;
}

void ParentChildComponentManager::EraseChild(EntityID parent, EntityID child)
{
  for (auto it = children[parent].begin(); it != children[parent].end(); ++it)
  {
    if (*it == child)
      children[parent].erase(it);
  }
}

void ParentChildComponentManager::EraseChild(EntityID parent, std::vector<EntityID>::iterator child)
{
  children[parent].erase(child);
}


void ParentChildComponentManager::ShutdownObject(EntityID id)
{
  children.erase(id);
  EraseChild(parents[id], id);
}
