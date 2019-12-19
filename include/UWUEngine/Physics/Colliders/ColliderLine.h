/******************************************************************************/
/*!
\par        Project Umbra
\file       Collider.h
\author     Yi Qian
\date       2019/12/05
\brief      Player Behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include "Collider.h"

class ColliderLine : public Collider
{
public:
	ColliderLine(EntityID ID, glm::vec2 start, glm::vec2 end);
	~ColliderLine() override;

  Collider* Clone() const override;
  void Serialize(std::ofstream& stream) const override;
  void Render() override;

	std::vector<Axis> const& GenerateAxis() override;
	Projection Project(Axis const& axis) const override;

  
private:
	glm::vec2 start;
	glm::vec2 end;
};
