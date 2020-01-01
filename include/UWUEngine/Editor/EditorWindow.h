/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorWindow.h
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <string>
#include <utility>

namespace Editors
{
  class Window
  {
  public:
    Window(std::string name, bool isActive = false) :name(std::move(name)), isActive(isActive) {}
    virtual ~Window() = default;

    void Render();
    void ToggleActive();
    bool IsActive();
    bool IsWindowNamed(std::string& name) const;
    const std::string& GetName() const;

  protected:
    virtual void Setup() = 0;
    virtual void Update() = 0;

  private:
    const std::string name;
    bool isActive;
  };
}
