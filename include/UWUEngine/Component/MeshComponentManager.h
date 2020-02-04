/******************************************************************************/
/*!
\par        Project Umbra
\file       MeshComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing meshes

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <GL/glew.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <map>
#include <tuple>

using Type = EntityManager::Type;
namespace UWUEngine
{
  class MeshComponentManager
  {
  public:
    MeshComponentManager();
    ~MeshComponentManager() = default;

    // Tuple Structure: <primitive_type, VAO, indices?>
    std::tuple<GLenum, GLuint, GLuint> getSquareMesh();
    std::tuple<GLenum, GLuint, GLuint> getLineMesh();
    std::tuple<GLenum, GLuint, GLuint> getCustomMesh(
      const std::vector<glm::vec3>& pos_vtx,
      const std::vector<glm::vec4>& clr_vtx,
      const std::vector<glm::vec2>& uv_vtx,
      std::vector <GLshort>& idx_vtx
    );
    //Leaked VRAM


    // square mesh 1x1 by default unless specify
    //Try to avoid leak
    void FreeMesh(std::tuple<GLenum, GLuint, GLuint> mesh);

    const std::tuple<GLenum, GLuint, GLuint>& GetEntityMesh();

  private:
    std::tuple<GLenum, GLuint, GLuint> primitive_type_vaoid_idx_cnt_entityMesh;
    std::tuple<GLenum, GLuint, GLuint> setup_vao_rect(
      const std::vector<glm::vec3>& pos_vtx,
      const std::vector<glm::vec4>& clr_vtx,
      const std::vector<glm::vec2>& uv_vtx,
      std::vector <GLshort>& idx_vtx);
    std::tuple<GLenum, GLuint, GLuint> setup_vao_line(
      const std::array<glm::vec3, 2>& pos_vtx,
      std::array <GLshort, 2>& idx_vtx, const std::array<glm::vec2, 2>& tex_vtx);
  };
}