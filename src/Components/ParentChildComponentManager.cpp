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

std::map<EntityID, ParentChildComponentManager::ParentAndChildren> ParentChildComponentManager::parentAndChildren;

const std::vector<EntityID>& ParentChildComponentManager::GetChildren(EntityID id)
{
  return parentAndChildren[id].children;
}

EntityID ParentChildComponentManager::GetParent(EntityID id)
{
  return parentAndChildren[id].parent;
}

void ParentChildComponentManager::AddChild(EntityID parent, EntityID child)
{
  parentAndChildren[parent].children.push_back(child);
  ParentChildComponentManager::Activate(child);
  parentAndChildren[child].parent = parent;
}

void ParentChildComponentManager::EraseChild(EntityID parent, EntityID child)
{
  auto& data = parentAndChildren[parent];
  for (auto it = data.children.begin(); it != data.children.end(); ++it)
  {
    if (*it == child)
      data.children.erase(it);
  }
}

void ParentChildComponentManager::EraseChild(EntityID parent, std::vector<EntityID>::iterator child)
{
  parentAndChildren[parent].children.erase(child);
}


void ParentChildComponentManager::ShutdownObject(EntityID id)
{
  parentAndChildren.erase(id);
}