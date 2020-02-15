#include <UWUEngine/Modules/VAOMod.h>
#include <UWUEngine/Graphics/Mesh.h>
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

VAOMod::VAOMod(ISpace* space) : System(space),
  vao_space_environment(Mesh::GetEntityMesh()),
  vao_space_ui(Mesh::GetEntityMesh()),
  vao_space_particle(Mesh::GetEntityMesh()),
  vao_space_debug(Mesh::GetEntityMesh()),
  vao_space_light(Mesh::GetEntityMesh())
{
}

VAOMod::~VAOMod()
{
  glDeleteVertexArrays(1, &std::get<1>(vao_space_environment));
  glDeleteVertexArrays(1, &std::get<1>(vao_space_ui));
  glDeleteVertexArrays(1, &std::get<1>(vao_space_particle));
  glDeleteVertexArrays(1, &std::get<1>(vao_space_debug));
  glDeleteVertexArrays(1, &std::get<1>(vao_space_light));
}

#pragma region Getter
const GLuint VAOMod::GetVAOEnvironment() const
{
  return std::get<1>(vao_space_environment);
}

const GLuint VAOMod::GetVAOUI() const
{
  return std::get<1>(vao_space_ui);
}

const GLuint VAOMod::GetVAOParticle() const
{
  return std::get<1>(vao_space_particle);
}

const GLuint VAOMod::GetVAODebug() const
{
  return std::get<1>(vao_space_debug);
}

const GLuint VAOMod::GetVAOLight() const
{
  return std::get<1>(vao_space_light);
}
#pragma endregion 

