/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorComponentViewer.h
\author     Yi Qian
\date       2019/12/29
\brief      Component viewer

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorWindow.h>
#include <UWUEngine/Editor/EditorComponent.h>
#include <unordered_map>
#include <memory>

namespace Editors
{
  class ComponentViewer final : public Window
  {
  public:
    ComponentViewer();
    ~ComponentViewer() override;
  protected:
    void Setup() override;
    void Update() override;
  private:
    std::unordered_map<std::string, std::shared_ptr<Component> > components;
  };
}
