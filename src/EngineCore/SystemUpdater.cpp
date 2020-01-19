#include <UWUEngine/SystemUpdater.h>

size_t SystemUpdater::init_firsts = static_cast<size_t>(SystemInitOrder::FIRST);
size_t SystemUpdater::update_firsts = static_cast<size_t>(SystemUpdateOrder::FIRST);
size_t SystemUpdater::init_lasts = static_cast<size_t>(SystemInitOrder::LAST);
size_t SystemUpdater::update_lasts = static_cast<size_t>(SystemUpdateOrder::LAST);

SystemUpdater::SystemUpdater()
{
  GetSystems();
}

void SystemUpdater::StartUp()
{
  static std::map<size_t, IConstructSystemHelper*> new_systems;
  for (auto& sys_help : GetSystems())
  {
    sys_help.second->Initialize();
    new_systems.insert(std::pair(static_cast<size_t>(sys_help.second->update_order_), sys_help.second));
  }
  std::swap(GetSystems(), new_systems);
}

void SystemUpdater::Update()
{
  for (auto& sys_help : GetSystems())
  {
    sys_help.second->system_->Update();
  }
}

std::map<size_t, IConstructSystemHelper*>& SystemUpdater::GetSystems()
{
  static std::map<size_t, IConstructSystemHelper*> systems;
  return systems;
}