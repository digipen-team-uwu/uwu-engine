#pragma once
#include <UWUEngine/System.h>

namespace UWUEngine
{

class HUDSys : public System
{
public:
  HUDSys(ISpace*);
  void DisplayFPS();
  void DisplayHealth();
  void DisplayEnergy();
  void Update() override;

private:
  EntityID fps;
  EntityID healthBar;
  EntityID energyBar;
};

}