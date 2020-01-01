/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderPolygon.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Polygon collider definition,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#define GLM_FORCE_SWIZZLE

#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Helper.h>
#include <glm/gtx/vector_angle.hpp>
#include <magic_enum.hpp>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Physics/Colliders/ColliderPolygon.h>

#ifdef  _DEBUG
#include <glm/gtx/transform.hpp>
GLSLShader ColliderPolygon::shader;
#endif

ColliderPolygon::ColliderPolygon(EntityID ID):
Collider(ID, ShapeType::RECTANGLE)
{
	InsertVertex({0.5, 0.5});
	InsertVertex({0.5, -0.5});
	InsertVertex({-0.5, 0.5});
	InsertVertex({-0.5, -0.5});
}

ColliderPolygon::ColliderPolygon(EntityID ID, glm::vec2 center):
Collider(ID, ShapeType::POLYGON), center(center)
{
}

ColliderPolygon::ColliderPolygon(EntityID ID, glm::vec2 center, const std::vector<glm::vec2>& vertices):
Collider(ID, ShapeType::POLYGON), center(center)
{
	for (auto& i : vertices)
	{
		InsertVertex(i);
	}
}

ColliderPolygon::~ColliderPolygon() = default;

Collider* ColliderPolygon::Clone() const
{
  return new ColliderPolygon(*this);
}

void ColliderPolygon::Serialize(std::ofstream& stream) const
{
  stream << "\"collider\" :\n";
  stream << "{\n";

  // Serialize body type
  stream << Tabs::THREE << R"("type" : ")" << magic_enum::enum_name(GetType()) << '"';

  switch (GetType())
  {
  case ShapeType::POLYGON:
    //TODO:Polygon serialization
    break;
  case ShapeType::RECTANGLE:
    break;
  default: ;
  }
  // Close the physics object
  stream << "}";
}

void ColliderPolygon::Render()
{
  #ifdef _DEBUG
  //If the vertex vector is empty, initialize it
  if (!shader.GetHandle())
  {
    if (!shader.CompileShaderFromFile(GL_VERTEX_SHADER, "./shaders/colliderShader.vert"))
    {
      TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load shader: \"./shaders/colliderShader.vert\"" << std::endl;
      exit(-1);
    }
    if (!shader.CompileShaderFromFile(GL_FRAGMENT_SHADER, "./shaders/colliderShader.frag"))
    {
      TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load shader: \"./shaders/colliderShader.frag\"" << std::endl;
      exit(-1);
    }
    shader.Link();
  }
  if (vertexLoop.empty())
  {
    for (auto i : vertices)
    {
      vertexLoop.push_back(i.second);
    }
  }

  //If the mesh doesn't exist, create it
  if (lineVAO == -1)
  {
    GLuint VBO, EBO;
    glGenVertexArrays(1, &lineVAO);
    glBindVertexArray(lineVAO);

    //Setup VBO
    glCreateBuffers(1, &VBO);
    glNamedBufferStorage(VBO,
      sizeof(glm::vec2) * vertexLoop.size(), nullptr,
      GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(VBO, 0,
      sizeof(glm::vec2) * vertexLoop.size(), vertexLoop.data());

    glCreateVertexArrays(1, &lineVAO);
    glEnableVertexArrayAttrib(lineVAO, 0);
    glVertexArrayVertexBuffer(lineVAO, 0, VBO, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(lineVAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(lineVAO, 0, 0);

    //Setup EBO
    glCreateBuffers(1, &EBO);
    std::vector<GLushort> indices; 
    for (int i = 0; i < vertexLoop.size(); i++)
    {
      indices.push_back(i);
    }
    glNamedBufferStorage(EBO,
      sizeof(GLushort) * indices.size(),
      reinterpret_cast<GLvoid*>(indices.data()),
      GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(lineVAO, EBO);
    glLineWidth(1);
  }

  glBindVertexArray(lineVAO);
  shader.Use();
  shader.SetUniform("model", TransformComponentManager::GetModelMatrix(ID));
  glDrawElements(GL_LINE_LOOP, vertexLoop.size(), GL_UNSIGNED_SHORT, nullptr);
  shader.UnUse();
  glBindVertexArray(0);

  #endif
}

void ColliderPolygon::InsertVertex(glm::vec2 vertex)
{
	const glm::vec2 angleVec = normalize(vertex - center);
	float angle = glm::angle(
		angleVec,
		{ 1, 0 });
	if (angleVec.y < 0)
	{
		angle = 2 * glm::pi<float>() - angle;
	}
	//TODO: Check convexity

	if (vertices.find(angle) != vertices.end())
	{
    TraceLogger::Log(TraceLogger::TRACE) << "Collider Vertex already in place." << std::endl;
		return;
	}
	vertices.emplace(angle, vertex);
	++verticesCount;
}

std::vector<Axis> const& ColliderPolygon::GenerateAxis()
{
	normals.clear();
	normals.reserve(verticesCount);
	const glm::mat4 model = TransformComponentManager::GetModelMatrix(ID);

	for(auto i = vertices.cbegin(); i != vertices.cend(); ++i)
	{
		glm::vec2 currVertex = model * glm::vec4(i->second, 0, 1);
		glm::vec2 nextVertex;
		auto next = std::next(i);
		if (next == vertices.cend())
		{
			nextVertex = model * glm::vec4(vertices.cbegin()->second, 0, 1);
		}
		else
		{
			nextVertex = model * glm::vec4(next->second, 0, 1);
		}
		glm::vec2 line = normalize(nextVertex - currVertex);
		glm::vec2 normal = { -line.y, line.x };
		normals.push_back(normal);
	}
	
	return normals;
}

Projection ColliderPolygon::Project(Axis const& axis) const
{
	const glm::mat4 model = TransformComponentManager::GetModelMatrix(ID);
	
	auto i = vertices.cbegin();
	glm::vec2 worldVertex = model * glm::vec4(i->second, 0, 1);
	float min = ProjectPoint(worldVertex, axis);
	float max = min;

	for (++i; i != vertices.cend(); ++i)
	{
		worldVertex = model * glm::vec4(i->second, 0, 1);
		const float projection = ProjectPoint(worldVertex, axis);
		if (projection < min)
		{
			min = projection;
		}
		if (projection > max)
		{
			max = projection;
		}
	}
	
	return Projection(min, max, axis);
}
