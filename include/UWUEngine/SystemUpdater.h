#pragma once
#include "SystemOrder.h"
#include <map>

class IConstructSystemHelper;

class SystemUpdater
{
public:
  SystemUpdater();
  static void StartUp();
  static void Update();
  template <typename T>
  static constexpr int AddSystem(SystemInitOrder init_order, SystemUpdateOrder update_order) noexcept;
private:
  static std::map<size_t, IConstructSystemHelper*>& GetSystems();
  static size_t init_firsts;
  static size_t update_firsts;
  static size_t init_lasts;
  static size_t update_lasts;
};

#include "SystemUpdater.inline.cpp" /* Template implementations. */