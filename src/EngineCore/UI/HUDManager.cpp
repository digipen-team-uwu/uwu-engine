/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       HUDManager.cpp
  \author     Hadi Alhussieni
  \date       2019/12/05
  \brief      Implementation for player's HUD

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/UI/HUDManager.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <iomanip>


EntityID HUDManager::fps = goc::INVALID_ID;
EntityID HUDManager::energyBar = goc::INVALID_ID;
EntityID HUDManager::healthBar = goc::INVALID_ID;

namespace wc = WindowConstants;

HUDManager::HUDManager()
{
  HUDManager::DisplayFPS();
  HUDManager::DisplayHealth();
  HUDManager::DisplayEnergy();
}

void HUDManager::DisplayFPS()
{
  if (fps == goc::INVALID_ID)
  {
    fps = EntityManager::New(EntityManager::Type::Text_);
    TextureComponentManager::Activate(fps);
    BehaviorComponentManager::Activate(fps);
    TransformComponentManager::Activate(fps);
    TransformComponentManager::SetTranslation({ -250.f + wc::WINDOW_WIDTH / 2.f, wc::WINDOW_HEIGHT / 2.f - 89.f, 0, 1 }, fps);
    TransformComponentManager::SetScale({ 30.f, 30.f, 1.f }, fps);
    TextureComponentManager::SetFilePath(fps, "./assets/coolfont.png");
    TextureComponentManager::SetDimensions(UIConstants::FONTSHEET_SIZE, fps);
    TextureComponentManager::SetColor(fps, { 1, 1, 1, 1 });
    EntityManager::SetClearImmunity(fps, true);
    EntityManager::SetDontSerialize(fps, true);
    TextureComponentManager::SetUV(fps, { -1.f,-1.f });
  }
}

void HUDManager::DisplayHealth()
{
  if (healthBar == goc::INVALID_ID)
  {
    healthBar = EntityManager::New(EntityManager::Type::HUDHealth);
    TextureComponentManager::Activate(healthBar);
    BehaviorComponentManager::Activate(healthBar);
    TransformComponentManager::Activate(healthBar);
    TransformComponentManager::SetTranslation({ 160.f - wc::WINDOW_WIDTH / 2.f, -89.f + wc::WINDOW_HEIGHT / 2.f, 0, 1 }, healthBar);
    TransformComponentManager::SetScale({ 50.f, 43.f, 1.f }, healthBar);
    TextureComponentManager::SetFilePath(healthBar, "./assets/UI/UI_FullHeart.png", 0);
    TextureComponentManager::SetFilePath(healthBar, "./assets/UI/UI_EmptyHeart.png", 1);
    EntityManager::SetClearImmunity(healthBar, true);
    EntityManager::SetDontSerialize(healthBar, true);
    TextureComponentManager::SetUV(healthBar, { -1.f,-1.f });
  }
}

void HUDManager::DisplayEnergy()
{
  if (energyBar == goc::INVALID_ID)
  {
    energyBar = EntityManager::New(EntityManager::Type::HUDEnergy);
    TextureComponentManager::Activate(energyBar);
    BehaviorComponentManager::Activate(energyBar);
    TransformComponentManager::Activate(energyBar);
    TransformComponentManager::SetTranslation({- wc::WINDOW_WIDTH / 2 + 80, wc::WINDOW_HEIGHT / 2 - 100, 0, 1 }, energyBar);
    TransformComponentManager::SetScale({ 273.f / 3, 487.f / 3, 1.f }, energyBar);
    TextureComponentManager::SetFilePath(energyBar, "./assets/UI/UI_Energy.png");
    EntityManager::SetClearImmunity(energyBar, true);
    EntityManager::SetDontSerialize(energyBar, true);
    TextureComponentManager::SetUV(energyBar, { -1.f,-1.f });
  }
}

void HUDManager::Update()
{
  if (fps != goc::INVALID_ID)
  {
    double frames = FrameRateController::GetFPS();
    int pres;
    pres = (frames > 99) ? 3 : 2;
    BehaviorComponentManager::GetBehavior<EntityManager::Type::Text_>(fps)->SetText() << "FPS: " << std::setprecision(pres) << frames;
  }
  if (healthBar != goc::INVALID_ID)
  {
    BehaviorComponentManager::GetBehavior<EntityManager::Type::HUDHealth>(healthBar)->SetHealth(PlayerData::GetHealth());
  }
  if (energyBar != goc::INVALID_ID)
  {
    BehaviorComponentManager::GetBehavior<EntityManager::Type::HUDEnergy>(energyBar)->SetEnergy(PlayerData::GetEnergy());
  }
}
