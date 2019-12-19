#pragma once
#include <UWUEngine/SystemUpdater.h>
#include <UWUEngine/BaseSystem.h>

class IConstructSystemHelper
{
public:
  SystemUpdateOrder update_order_ = SystemUpdateOrder::INVALID;
  IBaseSystem* system_ = nullptr;
  virtual void Initialize() = 0;
  virtual ~IConstructSystemHelper() = default;
};

template <typename T>
class ConstructSystemHelper : public IConstructSystemHelper
{
public:
  ConstructSystemHelper(SystemUpdateOrder update_order)
  {
    update_order_ = update_order;
  }
  void Initialize() override
  {
    system_ = new T();
  }
  ~ConstructSystemHelper() = default;
};

template <typename T>
constexpr int SystemUpdater::AddSystem(SystemInitOrder init_order, SystemUpdateOrder update_order) noexcept
{
  SystemInitOrder init_order_ = init_order;
  SystemUpdateOrder update_order_ = update_order;
  if (init_order_ != SystemInitOrder::INVALID && update_order_ != SystemUpdateOrder::INVALID)
  {
    if (init_order_ == SystemInitOrder::FIRST)
    {
      init_order_ = static_cast<SystemInitOrder>(init_firsts++);
    }
    if (update_order_ == SystemUpdateOrder::FIRST)
    {
      update_order_ = static_cast<SystemUpdateOrder>(update_firsts++);
    }
    if (init_order_ == SystemInitOrder::LAST)
    {
      init_order_ = static_cast<SystemInitOrder>(init_lasts++);
    }
    if (update_order_ == SystemUpdateOrder::LAST)
    {
      update_order_ = static_cast<SystemUpdateOrder>(init_lasts++);
    }
    GetSystems().insert(std::pair(static_cast<size_t>(init_order_), new ConstructSystemHelper<T>(update_order_)));
  }
  return static_cast<int>(update_order_);
}
