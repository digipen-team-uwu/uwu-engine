#include <UWUEngine/Systems/Order.h>

#include <UWUTest/Systems/HeadlessWindowSys.hpp>

namespace UWUEngine
{
  template <>
  SystemOrder GetSystemOrder<UWUTest::HeadlessWindowSys>()
  {
    return SystemOrder::Window;
  }

} // namespace UWUEngine
