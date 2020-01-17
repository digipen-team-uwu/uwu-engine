/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderCircle.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Circle collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Physics/Colliders/ColliderCircle.h>

ColliderCircle::ColliderCircle(EntityID ID, glm::vec2 center, float radius):
Collider(ID, ShapeType::CIRCLE), center_(center), radius_(radius)
{
}

ColliderCircle::~ColliderCircle()
{
}

Collider* ColliderCircle::Clone() const
{
  return new ColliderCircle(*this);
}

void ColliderCircle::Serialize(std::ofstream& stream) const
{
  //TODO: Circle collider serialization
}

void ColliderCircle::Render()
{
}

std::vector<Axis> const& ColliderCircle::GenerateAxis()
{
	return normals;
}

Projection ColliderCircle::Project(Axis const& axis) const
{
	return Projection({}, {}, axis);
}
