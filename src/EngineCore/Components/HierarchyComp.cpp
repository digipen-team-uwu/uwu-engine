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
#include <UWUEngine/Component/HierarchyComp.h>

using namespace UWUEngine;

EntityID Hierarchy::GetParent() const
{
  return parent_;
}

std::vector<EntityID>& Hierarchy::GetChild() const
{
  return children_;
}

void Hierarchy::AddChild(EntityID child)
{
  children_.push_back(child);
}

void Hierarchy::SetParent(EntityID parent)
{
  parent_ = parent;
}



Hierarchy HierarchyComp::operator[](EntityID ID)
{
  return Hierarchy(parents_[ID], children_[ID]);
}

const std::vector<EntityID>& HierarchyComp::GetChildren(EntityID id)
{
  Hierarchy parentChild = this->operator[](id);
  return parentChild.GetChild();
}

EntityID HierarchyComp::GetParent(EntityID id)
{
  Hierarchy parentChild = this->operator[](id);
  return parentChild.GetParent();
}

void HierarchyComp::AddChild(EntityID parent, EntityID child)
{
  Hierarchy parentChild = this->operator[](parent);
  parentChild.AddChild(child);
  //children[parent].push_back(child);
  //parents[child] = parent; ??????? -> dont understand
}

void HierarchyComp::SetParent(EntityID parent, EntityID child)
{
  (*this)[child].SetParent(parent);
}


void HierarchyComp::EraseChild(EntityID parent, EntityID child)
{
  Hierarchy parentChild = this->operator[](parent);
  for (auto it = parentChild.GetChild().begin(); it != parentChild.GetChild().end(); ++it)
  {
    if (*it == child)
    {
      parentChild.GetChild().erase(it);
      return;
    }
  }
}

void HierarchyComp::EraseChild(EntityID parent, std::vector<EntityID>::iterator child)
{
  Hierarchy parentChild = this->operator[](parent);
  parentChild.GetChild().erase(child);
}

void HierarchyComp::ShutdownObject(EntityID id)
{
  parents_[id] = 0;
  children_.erase(id);
  EraseChild(parents_[id], id);
}

