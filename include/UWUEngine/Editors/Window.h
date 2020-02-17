/******************************************************************************/
/*!
\par        Project Umbra
\file       Window.h
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <string>
#include <utility>
#include <UWUEngine/System.h>

namespace UWUEngine
{
  //Forward Declaration
  class ISpace;

  namespace Editors
  {
    class Window
    {
    public:
      Window(ISpace* systemSpace, std::string name, bool isActive = false, bool manual = false) :
      systemSpace(systemSpace), name(std::move(name)), isActive(isActive), manual(manual) {}
      virtual ~Window() = default;

      void Render();
      void ToggleActive();
      bool IsActive() const;
      bool IsWindowNamed(std::string& name) const;
      const std::string& GetName() const;

      template <class T>
      auto GetSystem() const -> std::enable_if_t<std::is_base_of_v<System, T>, T&>
      {
        const unsigned systemOrder = static_cast<unsigned>(GetOrder<T>());
        return *static_cast<T*>(systemSpace->GetObject(systemOrder));
      }

    protected:
      virtual void Setup() = 0;
      virtual void Update() = 0;
      bool* SetActive();

    private:
      ISpace* systemSpace;
      const std::string name;
      bool isActive;
      bool manual;
    };
  }
  
}
