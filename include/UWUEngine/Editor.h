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

#include <UWUEngine/System.h>

namespace UWUEngine
{

class EditorSys : public System
{
public:
  EditorSys(ISpace*);
  ~EditorSys();

  void Update() override;

  bool IsActive() const;

private:
  //Data
  bool isActive;

  //Function
  void ToggleActivate();
};

} // namespace UWUEngine
