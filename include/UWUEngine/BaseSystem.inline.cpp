#pragma once
#include "BaseSystem.h"
#include "SystemOrder.h"
#include "SystemUpdater.h"

template<typename T>
class RegisterSystemHelper
{
public:
  RegisterSystemHelper() = default;
protected:
  static int RegisterSystemHelper_ID;
};

template<typename T>
int RegisterSystemHelper<T>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<T>(SystemInitOrder::INVALID, SystemUpdateOrder::INVALID);

#define RegisterSystem(type, initOrder, updateOrder) \
  template<> \
  int RegisterSystemHelper<type>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<type>(SystemInitOrder::initOrder, SystemUpdateOrder::updateOrder);
