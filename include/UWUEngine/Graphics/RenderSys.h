/******************************************************************************/
/*!
\par        Project Umbra
\file       Render.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Rendering

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/constants.h>
#include <UWUEngine/System.h>

namespace UWUEngine
{

class RenderSys : public System
{
public:
  RenderSys(ISpace*);
  ~RenderSys() = default;
  void Update() override;
  static void DrawObject(EntityID ID);

private:

  // data member to represent geometric model to be rendered
  // C++ requires this object to have a definition in render.cpp!!!
};

}