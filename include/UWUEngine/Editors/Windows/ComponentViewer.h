/******************************************************************************/
/*!
\par        Project Umbra
\file       ComponentViewer.h
\author     Yi Qian
\date       2019/12/29
\brief      Component viewer

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editors/Window.h>
#include <UWUEngine/Editors/Component.h>
#include <unordered_map>
#include <memory>

namespace UWUEngine
{
  namespace Editors
  {
    class ComponentViewer final : public Window
    {
    public:
      ComponentViewer(ISpace* p);
      ~ComponentViewer() override;
    protected:
      void Setup() override;
      void Update() override;
    private:
      std::unordered_map<std::string, std::shared_ptr<Component> > components;
    };
  }
}
