#pragma once
#include <vector>
#include <unordered_map>
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/Component.h>


namespace UWUEngine
{
  class Hierarchy
  {
  public:
    Hierarchy(EntityID& parent, std::vector<EntityID>& children) : parent_(parent), children_(children) {}
    EntityID GetParent() const;
    std::vector<EntityID>& GetChild() const;
    void AddChild(EntityID child);
    void SetParent(EntityID parent);
  private:
    EntityID& parent_;
    std::vector<EntityID>& children_;
  };

  class HierarchyComp : public Component<HierarchyComp, Hierarchy>
  {
  public:
    HierarchyComp(ISpace *space) : Component(space) {}
    ~HierarchyComp() = default;

    void InitObject(EntityID ID) override {};
    void ShutdownObject(EntityID ID) override;

    Hierarchy operator[](EntityID ID);

    const std::vector<EntityID>& GetChildren(EntityID id);
    EntityID GetParent(EntityID id);
    void SetParent(EntityID parent, EntityID child);
    void AddChild(EntityID parent, EntityID child);
    void EraseChild(EntityID parent, EntityID child);
    void EraseChild(EntityID parent, std::vector<EntityID>::iterator child);

  private:
    EntityVector<EntityID> parents_{parent};
    std::unordered_map<EntityID, std::vector<EntityID>> children_;
  };

}