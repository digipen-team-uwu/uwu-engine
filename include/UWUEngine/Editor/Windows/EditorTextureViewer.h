/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorTextureViewer.h
\author     Yi Qian
\date       2019/02/06
\brief      Texture viewer

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorWindow.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineCompatibility.h>

namespace Editors
{
  class TextureViewer final : public Window
  {
  public:
    TextureViewer();
    ~TextureViewer() override;
  protected:
    void Setup() override;
    void Update() override;
  private:
    SingleTexture texture_;
  };
}
