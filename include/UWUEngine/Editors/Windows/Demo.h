/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.h
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editors/Window.h>

namespace UWUEngine
{
  namespace Editors
  {
    class Demo final : public Window
    {
    public:
      Demo(ISpace*);
      ~Demo() override;
    protected:
      void Setup() override;
      void Update() override;
    };
  }
}