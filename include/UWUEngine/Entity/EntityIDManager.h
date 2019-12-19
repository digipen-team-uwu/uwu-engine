#pragma once
#include <functional>
#include <map>
#include <UWUEngine/constants.h>

/*class EntityID
{
public:
  operator unsigned int() const { return EntityIDManager::indexes[pos]; }
private:
  unsigned int pos;
};

class EntityIDHasher
{
  size_t operator()(EntityID id) { return std::hash<unsigned int>()(id); }
};*/


class EntityIDManager
{
public:
  static void AddID(EntityID id);
  static void RemoveID(EntityID id);
  static unsigned int GetPos(EntityID id);
  static void ChangeIDPos(EntityID id, unsigned int newPos);
  static EntityID GetID(unsigned int pos);
  //friend class EntityID;
private:
  static std::map<EntityID, unsigned int> IDtoPos;
  static std::map<unsigned int, EntityID> PostoID;
};



