#pragma once
#include <vector>
#include <stack>
#include <unordered_map>
#include <UWUEngine/Component/Component.h>

namespace UWUEngine
{
  class EntityVectorBase
  {
  public:
    EntityVectorBase(ISpace* space);
    virtual void Resize(size_t size) = 0;
  };

  template<typename T>
  class EntityVector : EntityVectorBase
  {
  public:
    EntityVector(ISpace* space, size_t size = 0, T fill = {}) : EntityVectorBase(space), data(size, fill) {}
    auto operator[](size_t index) -> decltype(std::vector<T>().operator[](index))
    {
      return data[index];
    }

    T operator[](size_t index) const
    {
      return data[index];
    }

    T& get_ref(size_t index)
    {
      return data[index];
    }

    operator std::vector<T>& () { return data; }

    auto begin() -> decltype(std::vector<T>().begin())
    {
      return data.begin();
    }

    auto end() -> decltype(std::vector<T>().end())
    {
      return data.end();
    }

    virtual void Swap(EntityID pos1, EntityID pos2)
    {
      std::iter_swap(data.begin() + pos1, data.begin() + pos2);
    }

    virtual void Swap(EntityVector& rhs)
    {
      data.swap(rhs.data);
    }

    virtual void Resize(size_t size)
    {
      data.resize(size);
    }
  private:
    std::vector<T> data;
  };

  class Nothing {};

  class EntityComp : public Component <EntityComp, Nothing>
  {
  public:
    EntityComp(ISpace* space) : Component(space), vectorSize(0), idCount(0) {}

    enum Tag : uint64_t
    {
      STATIC = 1 << 0,
      FALLS = 1 << 1,
      HURTS = 1 << 2,
      BRIGHT = 1 << 3,
      EMITS = 1 << 4,
      EXPIRES = 1 << 5
    };

    void ResizeVectors();
    void AddVector(EntityVectorBase* vec);
    size_t GetVectorSize() const;

    void AddTag(EntityID id, Tag tag);
    void RemoveTag(EntityID id, Tag tag);
    bool HasTag(EntityID ID, Tag tag) const;
    void SetTags(EntityID id, Tag tag);
    Tag GetTags(EntityID ID) const;

    size_t GetIDCount() const;
    void SetIDCount(size_t count);
    std::stack<EntityID>& GetFreeIDs();
    std::vector<EntityID>& GetIDs();
    void SetDestroyed(EntityID id);

    void SetName(EntityID ID, std::string& name);
    bool HasName(EntityID ID);
    std::string GetName(EntityID ID);

    virtual void InitObject(EntityID ID) {};
    virtual void ShutdownObject(EntityID ID) {};
    std::stack<EntityID>& GetDestroyeds();
  private:
    std::vector<EntityVectorBase*> vectors;
    size_t vectorSize;
    size_t idCount;
    std::vector<EntityID> ids;
    std::stack<EntityID> freeIDs;
    std::unordered_map<EntityID, Tag> tags{};
    std::stack<EntityID> destroyed;
    std::unordered_map<EntityID, std::string> names;
  };
};
