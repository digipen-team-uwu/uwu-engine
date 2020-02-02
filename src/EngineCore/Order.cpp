#include <UWUEngine/Order.h>

#pragma region system_includes
#include <UWUEngine/WindowManager.h>
#pragma endregion 

using namespace UWUEngine;

template <> constexpr SystemOrder UWUEngine::GetOrder<SystemOrder, WindowManager>()
{
  return SystemOrder::Window;
}

