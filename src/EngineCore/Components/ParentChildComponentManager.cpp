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

using namespace UWUEngine;

EntityID ParentChild::GetParent() const
{
  return parent_;
}

std::vector<EntityID>& ParentChild::GetChild() const
{
  return children_;
}

void UWUEngine::ParentChild::AddChild(EntityID child)
{
  children_.push_back(child);
}

ParentChild UWUEngine::ParentChildComp::operator[](EntityID ID)
{
  return ParentChild(parents_[ID], children_[ID]);
}

const std::vector<EntityID>& ParentChildComp::GetChildren(EntityID id)
{
  ParentChild parentChild = this->operator[](id);
  return parentChild.GetChild();
}

EntityID ParentChildComp::GetParent(EntityID id)
{
  ParentChild parentChild = this->operator[](id);
  return parentChild.GetParent();
}

void ParentChildComp::AddChild(EntityID parent, EntityID child)
{
  ParentChild parentChild = this->operator[](parent);
  parentChild.AddChild(child);
  //children[parent].push_back(child);
  //parents[child] = parent; ??????? -> dont understand
}

void ParentChildComp::EraseChild(EntityID parent, EntityID child)
{
  ParentChild parentChild = this->operator[](parent);
  for (auto it = parentChild.GetChild().begin(); it != parentChild.GetChild().end(); ++it)
  {
    if (*it == child)
    {
      parentChild.GetChild().erase(it);
      return;
    }
  }
}

void ParentChildComp::EraseChild(EntityID parent, std::vector<EntityID>::iterator child)
{
  ParentChild parentChild = this->operator[](parent);
  parentChild.GetChild().erase(child);
}

void ParentChildComp::ShutdownObject(EntityID id)
{
  parents_[id] = 0;
  children_.erase(id);
  EraseChild(parents_[id], id);
}

