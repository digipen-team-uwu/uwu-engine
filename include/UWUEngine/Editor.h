/******************************************************************************/
/*!
\par        Project Umbra
\file       Editor.h
\author     Michael Rollosson Halbhuber
\date       2019/10/16
\brief      A class that allows for the editing of Game Objects and
            levels from within the engine.

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/BaseSystem.h>

class Editor : public BaseSystem<Editor>
{
public:
  Editor();
  ~Editor() override;

  void Update() override;

  static void Start();
  static void Stop();
  static bool IsActive();
};