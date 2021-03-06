/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorWindowManager.h
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <unordered_map>
#include <memory>

namespace Editors
{
  //Forward declaration
  class Window;

  class WindowManager
  {
  public:
    static void StartUp();
    static void Update();
    static void ToggleWindow(std::string& name);
    static std::shared_ptr<const Window> GetWindow(const std::string& name);
    static const std::unordered_map<std::string, std::shared_ptr<Window> > GetWindows();

  private:
    static std::unordered_map<std::string, std::shared_ptr<Window> > windows;
  };
}
