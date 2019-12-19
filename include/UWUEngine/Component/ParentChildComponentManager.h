#pragma once
#include <vector>
#include <map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>


class ParentChildComponentManager : public BaseComponent<ParentChildComponentManager>
{
public:
  ParentChildComponentManager() = default;
  ~ParentChildComponentManager() = default;
  void InitObject(EntityID ID) override {};
  void Update() override {};
  void ShutdownObject(EntityID ID) override;

  static const std::vector<EntityID> &GetChildren(EntityID id);
  static EntityID GetParent(EntityID id);
  static void AddChild(EntityID parent, EntityID child);
  static void EraseChild(EntityID parent, EntityID child);
  static void EraseChild(EntityID parent, std::vector<EntityID>::iterator child);
  
  struct ParentAndChildren
  {
    EntityID parent;
    std::vector<EntityID> children;
  };
private:
  static std::map<EntityID, ParentAndChildren> parentAndChildren;
};
