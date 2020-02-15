#include <UWUEngine/Component/EntityComp.h>

namespace UWUEngine
{

void EntityComp::AddTag(EntityID id, EntityComp::Tag tag)
{
  tags[id] = static_cast<Tag>(tags[id] | tag);
}

void EntityComp::SetTags(EntityID id, EntityComp::Tag tag)
{
  tags[id] = tag;
}

void EntityComp::RemoveTag(EntityID id, EntityComp::Tag tag)
{
  tags[id] = static_cast<Tag>(tags[id] & ~tag);
}

bool EntityComp::HasTag(EntityID ID, EntityComp::Tag tag) const
{
  return tags.at(ID) & tag;
}

std::stack<EntityID>& EntityComp::GetDestroyeds()
{
  return destroyed;
}

EntityComp::Tag EntityComp::GetTags(EntityID ID) const
{
  return tags.at(ID);
}

std::stack<EntityID>& EntityComp::GetFreeIDs()
{
  return freeIDs;
}

void EntityComp::SetDestroyed(EntityID id)
{
  destroyed.push(id);
}

void EntityComp::SetName(EntityID ID, std::string& name)
{
  names[ID] = name;
}

bool EntityComp::HasName(EntityID ID)
{
  return names.find(ID) == names.end();
}

std::string EntityComp::GetName(EntityID ID)
{
  return names[ID];
}

std::vector<EntityID>& EntityComp::GetIDs()
{
  return ids;
}

size_t EntityComp::GetIDCount() const
{
  return idCount;
}
void EntityComp::SetIDCount(size_t count)
{
  idCount = count;
}

void EntityComp::ResizeVectors()
{
  vectorSize *= 2;

  if (vectorSize == 0)
    vectorSize = 1;

  for (auto& it : vectors)
  {
    it->Resize(vectorSize);
  }
}

void EntityComp::AddVector(EntityVectorBase* vec)
{
  vectors.push_back(vec);
}

size_t EntityComp::GetVectorSize() const
{ 
  return vectorSize; 
}

EntityVectorBase::EntityVectorBase(ISpace* space)
{
  static_cast<EntityComp*>(space->GetObject(static_cast<unsigned>(GetOrder<EntityComp>())))->AddVector(dynamic_cast<EntityVectorBase*>(this));
}

}