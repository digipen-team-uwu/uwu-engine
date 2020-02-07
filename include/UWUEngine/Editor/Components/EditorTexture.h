/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorTexture.h
\author     Yi Qian
\date       2020/01/01
\brief      Texture Editor

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorComponent.h>
#include <UWUEngine/Graphics/SpineAnimation/SpineCompatibility.h>
#include <glm/glm.hpp>

namespace Editors
{
  class Texture final : public Component
  {
  public:
    Texture(const std::string& name);
    ~Texture() override;

  protected:
    void CheckActive(EntityID id) override;
    void UpdateComponent(EntityID id) override;
    void UpdateUI() override;

  private:
    glm::vec2* uv;
    glm::vec4* color;
    std::string path;
    SingleTexture texture_;
  };
}
