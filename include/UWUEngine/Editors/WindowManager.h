/******************************************************************************/
/*!
\par        Project Umbra
\file       WindowManager.h
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <unordered_map>
#include <memory>

namespace UWUEngine
{
  class ISpace;

  namespace Editors
  {
    //Forward declaration
    class Window;

    class WindowManager
    {
    public:
      explicit WindowManager(ISpace* systemSpace);
      void Update();
      void ToggleWindow(std::string& name);
      std::shared_ptr<const Window> GetWindow(const std::string& name);
      [[nodiscard]] std::unordered_map<std::string, std::shared_ptr<Window> > & GetWindows();

    private:
      ISpace* systemSpace;
      std::unordered_map<std::string, std::shared_ptr<Window> > windows;
    };
  }
  
}
