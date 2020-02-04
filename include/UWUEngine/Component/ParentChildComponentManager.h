#pragma once
#include <vector>
#include <unordered_map>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>


namespace UWUEngine
{
  class ParentChild
  {
  public:
    ParentChild(EntityID& parent, std::vector<EntityID>& children) : parent_(parent), children_(children) {}
    EntityID GetParent() const;
    std::vector<EntityID>& GetChild() const;
    void AddChild(EntityID child);
  private:
    EntityID& parent_;
    std::vector<EntityID>& children_;
  };

  class ParentChildComponentManager
  {
  public:
    ParentChildComponentManager() = default;
    ~ParentChildComponentManager() = default;

    void InitObject(EntityID ID) override {};
    void Update() override {};
    void ShutdownObject(EntityID ID) override;

    ParentChild operator[](EntityID ID);

    const std::vector<EntityID>& GetChildren(EntityID id);
    EntityID GetParent(EntityID id);
    void AddChild(EntityID parent, EntityID child);
    void EraseChild(EntityID parent, EntityID child);
    void EraseChild(EntityID parent, std::vector<EntityID>::iterator child);

  private:
    EntityVector<EntityID> parents_;
    std::unordered_map<EntityID, std::vector<EntityID>> children_;
  };

}
