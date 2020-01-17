/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderPoint.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Point collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Physics/Colliders/ColliderPoint.h>

ColliderPoint::ColliderPoint(EntityID ID):
Collider(ID,ShapeType::POINT), position(0, 0)
{
}

ColliderPoint::ColliderPoint(EntityID ID, glm::vec2 position):
Collider(ID, ShapeType::POINT), position(position)
{
}

ColliderPoint::~ColliderPoint() = default;

Collider* ColliderPoint::Clone() const
{
  return new ColliderPoint(*this);
}

void ColliderPoint::Serialize(std::ofstream& stream) const
{
  //TODO:Point collider serialization
}

void ColliderPoint::Render()
{
}

std::vector<Axis> const& ColliderPoint::GenerateAxis()
{
	return normals;
}

Projection ColliderPoint::Project(Axis const& axis) const
{
	return Projection({}, {}, axis);
}
