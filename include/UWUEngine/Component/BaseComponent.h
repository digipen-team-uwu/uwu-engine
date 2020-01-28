#pragma once
#include <vector>
#include <UWUEngine/constants.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityVector.h>

template<typename T>
class RegisterComponentHelper
{
public:
  RegisterComponentHelper() = default;
protected:
  static size_t RegisterComponentHelper_ID;
};

class IBaseComponent
{
public:
  virtual void Update() = 0;
  virtual void InitObject(EntityID ID) = 0;
  virtual void ShutdownObject(EntityID ID) = 0;
  virtual void Make_Inactive(EntityID) = 0; // HACK
  virtual ~IBaseComponent() = default;
};

template<typename T>
class BaseComponent : public IBaseComponent, public RegisterComponentHelper<T>
{
public:
  
  BaseComponent() = default;
  ~BaseComponent() = default;
  // you cannot copy or move a component object!
  BaseComponent(const BaseComponent&) = delete;
  void operator=(const BaseComponent&) = delete;
  BaseComponent(const BaseComponent&&) = delete;
  void operator=(const BaseComponent&&) = delete;

  void Make_Inactive(EntityID ID) final override
  {
    Deactivate(ID);
  };

  static void Activate(EntityID ID)
  {
    if (!isActive_[ID])
    {
      isActive_[ID] = true;
      const auto component = EntityManager::GetComponents().at(updateOrder_);
      component->Get()->InitObject(ID);
    }
  }
  static void Deactivate(EntityID ID)
  {
    if (isActive_[ID])
    {
      isActive_[ID] = false;
      const auto component = EntityManager::GetComponents().at(updateOrder_);
      component->Get()->ShutdownObject(ID);
    }
  }
  static bool IsActive(EntityID ID)
  {
    return isActive_[ID];
  }
  static size_t updateOrder_;
private:
  static EntityVector<std::uint8_t> isActive_;
  
};

template<typename T>
EntityVector<std::uint8_t> BaseComponent<T>::isActive_(GameObjectConstants::INITIAL_OBJECT_COUNT);

template<typename T>
size_t BaseComponent<T>::updateOrder_ = static_cast<size_t>(ComponentUpdateOrder::INVALID);

template<typename T>
size_t RegisterComponentHelper<T>::RegisterComponentHelper_ID = EntityManager::template AddComponent<T>(ComponentUpdateOrder::INVALID);

#define RegisterComponent(type, updateOrder) \
template<> \
size_t RegisterComponentHelper<type>::RegisterComponentHelper_ID = EntityManager::AddComponent<type>(ComponentUpdateOrder::updateOrder);
