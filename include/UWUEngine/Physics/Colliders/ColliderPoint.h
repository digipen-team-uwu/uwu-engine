/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderPoint.h
\author     Yi Qian
\date       2019/12/05
\brief      Point Collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include "Collider.h"

class ColliderPoint : public Collider
{
public:
	ColliderPoint(EntityID ID);
	ColliderPoint(EntityID ID, glm::vec2 position);
	~ColliderPoint() override;

  Collider* Clone() const override;
  void Serialize(std::ofstream& stream) const override;
  void Render() override;
	
	std::vector<Axis> const& GenerateAxis() override;
	[[nodiscard]] Projection Project(Axis const& axis) const override;

private:
	glm::vec2 position;
};
