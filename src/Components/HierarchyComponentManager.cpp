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
#include <UWUEngine/Component/HierarchyComponentManager.h>

template<>
size_t RegisterComponentHelper<HierarchyComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<HierarchyComponentManager>(ComponentUpdateOrder::LAST);

std::unordered_map<EntityID, std::vector<EntityID>> HierarchyComponentManager::children;

EntityVector<EntityID> HierarchyComponentManager::parents(goc::INITIAL_OBJECT_COUNT);

const std::vector<EntityID>& HierarchyComponentManager::GetChildren(EntityID id)
{
  return children[id];
}

EntityID HierarchyComponentManager::GetParent(EntityID id)
{
  return parents[id];
}

void HierarchyComponentManager::AddChild(EntityID parent, EntityID child)
{
 children[parent].push_back(child);
  HierarchyComponentManager::Activate(child);
  parents[child] = parent;
}

void HierarchyComponentManager::EraseChild(EntityID parent, EntityID child)
{
  for (auto it = children[parent].begin(); it != children[parent].end(); ++it)
  {
    if (*it == child)
    {
      children[parent].erase(it);
      return;
    }
  }
}

void HierarchyComponentManager::EraseChild(EntityID parent, std::vector<EntityID>::iterator child)
{
  children[parent].erase(child);
}


void HierarchyComponentManager::ShutdownObject(EntityID id)
{
  children.erase(id);
  EraseChild(parents[id], id);
}
