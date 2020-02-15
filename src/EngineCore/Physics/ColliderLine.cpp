/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderLine.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Line Collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Physics/Colliders/ColliderLine.h>

namespace UWUEngine
{

ColliderLine::ColliderLine(ColliderComp& p, EntityID ID, glm::vec2 start, glm::vec2 end) :
  Collider(p, ID, ShapeType::LINE), start(start), end(end)
{}

ColliderLine::~ColliderLine()
{}

Collider* ColliderLine::Clone() const
{
  return new ColliderLine(*this);
}

void ColliderLine::Serialize(std::ofstream& stream) const
{
  //TODO:Line Collider serialization
}

void ColliderLine::Render()
{}

std::vector<Axis> const& ColliderLine::GenerateAxis()
{
  return normals;
}

Projection ColliderLine::Project(Axis const& axis) const
{
  return Projection({}, {}, axis);
}

}
