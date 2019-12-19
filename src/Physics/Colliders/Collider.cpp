/******************************************************************************/
/*!
\par        Project Umbra
\file       Collider.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Base collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Physics/Colliders/Collider.h>

float ProjectPoint(glm::vec2 point, Axis axis)
{
	return glm::dot(point, axis);
}

Projection::Projection(float min, float max, Axis axis):
min(min), max(max), axis(axis)
{
}

bool Projection::isOverlapping(Projection const& rhs) const
{
#ifdef _DEBUG
	assert(axis == rhs.axis);
#endif

	if (min > rhs.max || max < rhs.min)
	{
		return false;
	}
	return true;
}

float Projection::getOverlap(Projection const& rhs) const
{
#ifdef _DEBUG
	assert(axis == rhs.axis);
#endif
	return glm::min(max, rhs.max) - glm::max(min, rhs.min);
}

CollisionInfo Collider::IsColliding(Collider& rhs)
{
	float minDepth = std::numeric_limits<float>::max();
	glm::vec2 direction = {0, 0};
	// update normals
	for (auto i : GenerateAxis())
	{
		Projection proj1 = Project(i);
		Projection proj2 = rhs.Project(i);

		if (!proj1.isOverlapping(proj2))
		{
			return {};
		}
		const float overlap = proj1.getOverlap(proj2);
		if (overlap < minDepth)
		{
			minDepth = overlap;
			direction = i;
		}
	}
	for (auto i : rhs.GenerateAxis())
	{
		Projection proj1 = Project(i);
		Projection proj2 = rhs.Project(i);

		if (!proj1.isOverlapping(proj2))
		{
			return {};
		}
		const float overlap = proj1.getOverlap(proj2);
		if (overlap < minDepth)
		{
			minDepth = overlap;
			direction = i;
		}
	}
	return {ID, rhs.ID, direction, minDepth};
}

Collider::ShapeType Collider::GetType() const
{
	return type;
}

void Collider::SetType(ShapeType type)
{
	this->type = type;
}
