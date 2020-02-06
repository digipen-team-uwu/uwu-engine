#pragma once
#include <vector>
#include <algorithm>
#include <list>
#include <UWUEngine/constants.h>
#include <UWUEngine/Entity/EntityIDManager.h>
#include <UWUEngine/System.h>

namespace UWUEngine
{

class EntityVectorBase
{
public:
  EntityVectorBase() = default;
  virtual void Swap(unsigned int pos1, unsigned int pos2) = 0;
  virtual void Resize(size_t size) = 0;
};

class EntityVectorManager : public System
{
public:
  template<typename T>
  static void QuickSortBy(std::vector<T>& sort, int low = 0, int high = vectorSize - 1)
  {
    if (low < high)
    {
      int part = Partition<T>(sort, low, high);
      QuickSortBy<T>(sort, low, part - 1);
      QuickSortBy<T>(sort, part + 1, high);
    }
  }

  static void ResizeVectors()
  {
    vectorSize *= 2;

    if (vectorSize == 0)
      vectorSize = 1;

    for (auto& it : GetVectors())
    {
      it->Resize(vectorSize);
    }
  }

  template<typename T>
  static int Partition(std::vector<T>& sort, int low, int high)
  {
    T pivot = sort[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
      if (sort[j] < pivot)
      {
        ++i;
        for (auto& it : GetVectors())
        {
          it->Swap(i, j);
        }
        EntityIDManager::ChangeIDPos(EntityIDManager::GetID(i), j);
        EntityIDManager::ChangeIDPos(EntityIDManager::GetID(j), i);
      }
    }
    for (auto& it : GetVectors())
    {
      it->Swap(i + 1, high);
    }
    EntityIDManager::ChangeIDPos(EntityIDManager::GetID(i + 1), high);
    EntityIDManager::ChangeIDPos(EntityIDManager::GetID(high), i + 1);
    return i + 1;
  }

  template<typename> friend class EntityVector;

  static size_t GetVectorSize() { return vectorSize; }
private:
  static std::vector<EntityVectorBase*>& GetVectors() { static std::vector<EntityVectorBase*> vectors; return vectors; }
  static size_t vectorSize;
};

template<typename T>
class EntityVector : EntityVectorBase
{
public:
  EntityVector() = default;
  EntityVector(size_t size, T fill = {}) : data(size, fill)
  {
    EntityVectorManager::GetVectors().push_back(dynamic_cast<EntityVectorBase*>(this));
  }
  auto operator[](size_t index) -> decltype(std::vector<T>().operator[](index))
  {
    //return data[EntityIDManager::GetPos(index)]; 
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

  virtual void Resize(size_t size)
  {
    data.resize(size);
  }
private:
  std::vector<T> data;
};

}
