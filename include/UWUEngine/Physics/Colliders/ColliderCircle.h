/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderCircle.h
\author     Yi Qian
\date       2019/12/05
\brief      Circle collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <UWUEngine/Component/ColliderComp.h>

namespace UWUEngine
{

class ColliderCircle : public Collider
{
public:
	ColliderCircle(ColliderComp& p, EntityID ID, glm::vec2 center, float radius);
	~ColliderCircle() override;

	Collider* Clone() const override;
	void Serialize(std::ofstream& stream) const override;
	void Render() override;

	std::vector<Axis> const& GenerateAxis() override;
	[[nodiscard]] Projection Project(Axis const& axis) const override;


private:
	glm::vec2 center_;
	float radius_;
};

}
