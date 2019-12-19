#pragma once
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/constants.h>

class HUDManager : public BaseSystem<HUDManager>
{
  public:
    HUDManager();
    static void DisplayFPS();
    static void DisplayHealth();
    static void DisplayEnergy();
    void Update() override;


  private:
    static EntityID fps;
    static EntityID healthBar;
    static EntityID energyBar;
};
