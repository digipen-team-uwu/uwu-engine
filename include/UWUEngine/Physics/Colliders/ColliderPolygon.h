/******************************************************************************/
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
#include "Collider.h"
#include "map"

//#ifdef _DEBUG
#include <UWUEngine/Graphics/Shader/glslshader.h>
//#endif

class ColliderPolygon : public Collider
{
public:
	ColliderPolygon(EntityID ID);
	ColliderPolygon(EntityID ID, glm::vec2 center);
	ColliderPolygon(EntityID ID, glm::vec2 center, const std::vector<glm::vec2>& vertices);
	~ColliderPolygon() override;

  Collider* Clone() const override;
  void Serialize(std::ofstream& stream) const override;
  void Render() override;
	
	void InsertVertex(glm::vec2 vertex);

private:
	size_t verticesCount{0};
	glm::vec2 center{0, 0};
	std::map<float, glm::vec2> vertices;

  //#ifdef  _DEBUG
  GLuint lineVAO{static_cast<GLuint>(-1)};
  static GLSLShader shader;

  std::vector<glm::vec2> vertexLoop;
  //#endif

	Projection Project(Axis const& axis) const override;
	std::vector<Axis> const& GenerateAxis() override;
};
