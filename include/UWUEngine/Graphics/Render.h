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
#include <UWUEngine/BaseSystem.h>

class Render : public BaseSystem<Render>
{
public:
  Render();
  ~Render() = default;
  void Update() override;
};
