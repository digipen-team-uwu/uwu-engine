/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       TextObject.cpp
  \author     Hadi Alhussieni
  \date       2019/10/06
  \brief      Implementation for behaviors for text type objects. Includes storing
              strings and specially rendering them using a font sheet.

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Behaviors/TextObject.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Graphics/Render.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/UI/UIManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include "UWUEngine/Graphics/Texture/AtlasModule.h"
typedef EntitySys::Type type;

void Behavior<type::Text_>::Update()
{
  Render();
}
void Behavior<type::Text_>::Render()
{
  std::string s = formattedText.str();
  const char *it = s.c_str();
  glm::vec4 oldTrans = TransformComponentManager::GetTranslation(GetID());
  glm::vec4 offset = {};
  offset.x = 0.f;

  //TransformComponentManager::SetTranslation(TransformComponentManager::GetTranslation(GetID()) - offset, GetID());

  while (*it)
  {
    UIManager::PushElement(0, TransformComponentManager::GetTranslation(GetID()) + offset, TransformComponentManager::GetScale(GetID()), 
                             TextureComponentManager::GetColor(GetID()), AnimationComponentManager::indexToUvs(GetID(), *it - ' '), 
                                TextureComponentManager::GetDimensions(GetID()), TextureAtlaser::GetAtlasUV(GetID()),
                              TextureAtlaser::GetAtlasScale(GetID()), TextureAtlaser::GetAtlasLayers(GetID()));
    offset.x += 30.f;
     //TransformComponentManager::SetTranslation(TransformComponentManager::GetTranslation(GetID()) + offset, GetID());
     //TextureComponentManager::SetUV(GetID(), AnimationComponentManager::indexToUvs(GetID(), *it - ' '));
     //Render::DrawObject(GetID());
     it++;
  }
  //TransformComponentManager::SetTranslation(oldTrans, GetID());
}