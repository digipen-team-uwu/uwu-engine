#pragma once

#include <UWUEngine/System.h>

namespace UWUEngine
{
class ColliderSys final : public System
{
public:
  ColliderSys(ISpace* p);
  ~ColliderSys() override = default;
  void Update() override;
};
}
