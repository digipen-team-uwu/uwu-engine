/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorPhysics.h
\author     Yi Qian
\date       2020/01/01
\brief      Physics Editor

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorComponent.h>

#include <glm/glm.hpp>

namespace Editors
{
  class Physics final : public Component
  {
  public:
    Physics(const std::string& name);
    ~Physics() override;

  protected:
    void CheckActive(EntityID id) override;
    void UpdateComponent(EntityID id) override;
    void UpdateUI() override;
  private:
    Element<float> inverseMass{"Inverse mass"};
    Element<glm::vec3> velocity{"Velocity"};
    Element<glm::vec3> acceleration{"Acceleration"};
    Element<glm::vec3> drag{"Drag"};
    Element<float> rotationalVel{"Angular Velocity"};
  };
}
