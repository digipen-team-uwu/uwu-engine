#include <UWUEngine/Entity/EntityIDManager.h>

std::map<EntityID, unsigned int> EntityIDManager::IDtoPos;
std::map<unsigned int, EntityID> EntityIDManager::PostoID;

void EntityIDManager::AddID(EntityID id) 
{ 
  PostoID[id] = id;
  IDtoPos[id] = id;
}

void EntityIDManager::RemoveID(EntityID id) 
{ 
  PostoID.erase(IDtoPos[id]);
  IDtoPos.erase(id);
}

unsigned int EntityIDManager::GetPos(EntityID id)
{ 
  return IDtoPos[id];
}

EntityID EntityIDManager::GetID(unsigned int pos)
{
  return PostoID[pos];
}

void EntityIDManager::ChangeIDPos(EntityID id, unsigned int newPos)
{ 
  IDtoPos[id] = newPos;
  PostoID[newPos] = id;
}