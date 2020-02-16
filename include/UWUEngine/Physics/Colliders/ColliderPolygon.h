﻿/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderPolygon.h
\author     Yi Qian
\date       2019/12/05
\brief      Polygon Collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <UWUEngine/Component/ColliderComp.h>
#include <map>

//#ifdef _DEBUG
#include <UWUEngine/Graphics/GLSLShader.h>
//#endif

namespace UWUEngine
{

class ColliderPolygon : public Collider
{
public:
	ColliderPolygon(ColliderComp& p, EntityID ID);
	ColliderPolygon(ColliderComp& p, EntityID ID, glm::vec2 center);
	ColliderPolygon(ColliderComp& p, EntityID ID, glm::vec2 center, const std::vector<glm::vec2>& vertices);
	~ColliderPolygon() override;

	Collider* Clone() const override;
	void Render() override;

	void InsertVertex(glm::vec2 vertex);

private:
	size_t verticesCount{ 0 };
	glm::vec2 center{ 0, 0 };
	std::map<float, glm::vec2> vertices;

	//#ifdef  _DEBUG
	GLuint lineVAO{ static_cast<GLuint>(-1) };

	std::vector<glm::vec2> vertexLoop;
	//#endif

	Projection Project(Axis const& axis) const override;
	std::vector<Axis> const& GenerateAxis() override;
};

}