#pragma once
#include <tuple>
#include <GL/glew.h>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <array>

namespace UWUEngine
{
  namespace Mesh
  {
    // Tuple Structure: <primitive_type, VAO, indices?>
    std::tuple<GLenum, GLuint, GLuint> getSquareMesh();
    std::tuple<GLenum, GLuint, GLuint> getLineMesh();
    std::tuple<GLenum, GLuint, GLuint> getCustomMesh(
      const std::vector<glm::vec3>& pos_vtx,
      const std::vector<glm::vec4>& clr_vtx,
      const std::vector<glm::vec2>& uv_vtx,
      std::vector <GLshort>& idx_vtx
    );

    const std::tuple<GLenum, GLuint, GLuint> GetEntityMesh();

    std::tuple<GLenum, GLuint, GLuint> setup_vao_rect(
      const std::vector<glm::vec3>& pos_vtx,
      const std::vector<glm::vec4>& clr_vtx,
      const std::vector<glm::vec2>& uv_vtx,
      std::vector <GLshort>& idx_vtx);
    std::tuple<GLenum, GLuint, GLuint> setup_vao_line(
      const std::array<glm::vec3, 2>& pos_vtx,
      std::array <GLshort, 2>& idx_vtx, const std::array<glm::vec2, 2>& tex_vtx);
    
  }
}