/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorTransform.h
\author     Yi Qian
\date       2019/12/31
\brief      Transform Editor

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorComponent.h>
#include <glm/glm.hpp>

namespace Editors
{
  class Transform final : public Component
  {
  public:
    Transform(std::string name);
    ~Transform() override = default;

  protected:
    void CheckActive(EntityID id) override;
    void UpdateUI() override;
    void UpdateComponent(EntityID id) override;

  private:
    Element<glm::vec3> translation{"Translation"};
    Element<float> rotation{"Rotation"};
    Element<glm::vec3> scale{"Scale"};
  };
}
