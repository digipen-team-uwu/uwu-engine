/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       HUDSys.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for player's HUD

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/UI/HUDSys.h>
#include <UWUEngine/FrameLimiterSys.h>
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/constants.h>
#include <iomanip>

namespace wc = WindowConstants;

namespace UWUEngine
{

HUDSys::HUDSys(ISpace* p) : System(p), fps(goc::INVALID_ID), healthBar(goc::INVALID_ID), energyBar(goc::INVALID_ID)
{
  DisplayFPS();
  DisplayHealth();
  DisplayEnergy();
}

void HUDSys::DisplayFPS()
{
  if (fps == goc::INVALID_ID)
  {
    fps = EntitySys::New(EntitySys::Type::Text_);
    TextureComponentManager::Activate(fps);
    BehaviorComp::Activate(fps);
    TransformComponentManager::Activate(fps);
    TransformComponentManager::SetTranslation({ -250.f + wc::WINDOW_WIDTH / 2.f, wc::WINDOW_HEIGHT / 2.f - 89.f, 0, 1 }, fps);
    TransformComponentManager::SetScale({ 30.f, 30.f, 1.f }, fps);
    TextureComponentManager::SetFilePath(fps, "./assets/coolfont.png");
    TextureComponentManager::SetDimensions(UIConstants::FONTSHEET_SIZE, fps);
    TextureComponentManager::SetColor(fps, { 1, 1, 1, 1 });
    EntitySys::SetClearImmunity(fps, true);
    EntitySys::SetDontSerialize(fps, true);
    TextureComponentManager::SetUV(fps, { -1.f,-1.f });
  }
}

void HUDSys::DisplayHealth()
{
  if (healthBar == goc::INVALID_ID)
  {
    healthBar = EntitySys::New(EntitySys::Type::HUDHealth);
    TextureComponentManager::Activate(healthBar);
    BehaviorComp::Activate(healthBar);
    TransformComponentManager::Activate(healthBar);
    TransformComponentManager::SetTranslation({ 160.f - wc::WINDOW_WIDTH / 2.f, -89.f + wc::WINDOW_HEIGHT / 2.f, 0, 1 }, healthBar);
    TransformComponentManager::SetScale({ 50.f, 43.f, 1.f }, healthBar);
    TextureComponentManager::SetFilePath(healthBar, "./assets/UI/UI_FullHeart.png", 0);
    TextureComponentManager::SetFilePath(healthBar, "./assets/UI/UI_EmptyHeart.png", 1);
    EntitySys::SetClearImmunity(healthBar, true);
    EntitySys::SetDontSerialize(healthBar, true);
    TextureComponentManager::SetUV(healthBar, { -1.f,-1.f });
  }
}

void HUDSys::DisplayEnergy()
{
  if (energyBar == goc::INVALID_ID)
  {
    energyBar = EntitySys::New(EntitySys::Type::HUDEnergy);
    TextureComponentManager::Activate(energyBar);
    BehaviorComp::Activate(energyBar);
    TransformComponentManager::Activate(energyBar);
    TransformComponentManager::SetTranslation({ -wc::WINDOW_WIDTH / 2 + 80, wc::WINDOW_HEIGHT / 2 - 100, 0, 1 }, energyBar);
    TransformComponentManager::SetScale({ 273.f / 3, 487.f / 3, 1.f }, energyBar);
    TextureComponentManager::SetFilePath(energyBar, "./assets/UI/UI_Energy.png");
    EntitySys::SetClearImmunity(energyBar, true);
    EntitySys::SetDontSerialize(energyBar, true);
    TextureComponentManager::SetUV(energyBar, { -1.f,-1.f });
  }
}

void HUDSys::Update()
{
  if (fps != goc::INVALID_ID)
  {
    double frames = Get<FrameLimiterSys>().GetFPS();
    int pres;
    pres = (frames > 99) ? 3 : 2;
    BehaviorComp::GetBehavior<EntitySys::Type::Text_>(fps)->SetText() << "FPS: " << std::setprecision(pres) << frames;
  }
  if (healthBar != goc::INVALID_ID)
  {
    BehaviorComp::GetBehavior<EntitySys::Type::HUDHealth>(healthBar)->SetHealth(PlayerData::GetHealth());
  }
  if (energyBar != goc::INVALID_ID)
  {
    BehaviorComp::GetBehavior<EntitySys::Type::HUDEnergy>(energyBar)->SetEnergy(PlayerData::GetEnergy());
  }
}

} // namespace UWUEngine
