/******************************************************************************/
/*!
\par        Project Umbra
\file       Collider.h
\author     Yi Qian
\date       2019/12/05
\brief      Base Collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <UWUEngine/constants.h>
#include <fstream>

using Axis = glm::vec2;
class ColliderComponentManager;

/**
 * \brief Project the point onto an axis
 * \param point The point to project from
 * \param axis The axis to project onto
 * \return The resultant point
 */
float ProjectPoint(glm::vec2 point, Axis axis);

class Projection
{
public:
	Projection(float min, float max, Axis axis);
	[[nodiscard]] bool isOverlapping(Projection const& rhs) const;
	[[nodiscard]] float getOverlap(Projection const& rhs)const;
	
private:
	float min{};
	float max{};
	const Axis axis;
};

struct CollisionInfo
{
	EntityID obj1{0};
	EntityID obj2{0};
	glm::vec2 direction{0, 0};
	float depth{0};

	CollisionInfo() = default;
};

class Collider
{
public:
	enum class ShapeType
	{
		INACTIVE,
		INVALID,
		POINT,
		LINE,
		CIRCLE,
		POLYGON,
		RECTANGLE,
		COUNT
	};
	Collider(EntityID ID, ShapeType type):ID(ID), type(type){}
	virtual ~Collider() = default;
	Collider(Collider const&) = default;
	Collider& operator=(Collider const&) = default;

  [[nodiscard]] virtual Collider* Clone() const = 0;
  virtual void Serialize(std::ofstream& stream) const = 0;
  virtual void Render() = 0;

	CollisionInfo IsColliding(Collider& rhs);

	[[nodiscard]] virtual Projection Project(Axis const& axis) const = 0;
	virtual std::vector<Axis> const& GenerateAxis() = 0;

	[[nodiscard]] ShapeType GetType() const;
	void SetType(ShapeType type);

  friend ColliderComponentManager;

protected:

	std::vector<Axis> normals;
	EntityID ID;

private:
	ShapeType type;
};
