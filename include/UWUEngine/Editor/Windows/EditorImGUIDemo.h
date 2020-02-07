/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.h
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorWindow.h>

namespace Editors
{
  class Demo final : public Window
  {
  public:
    Demo();
    ~Demo() override;
  protected:
    void Setup() override;
    void Update() override;
  };
}
