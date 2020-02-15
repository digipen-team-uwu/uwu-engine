#include <UWUEngine/Graphics/Mesh.h>

const std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::GetEntityMesh()
{
  return getSquareMesh();
}

// square mesh 1x1 by default unless specify
std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::getSquareMesh()
{
    // positions
    std::vector<glm::vec3> pos_vtx(4);
    pos_vtx[0] = { -0.5f,  -0.5f, 0.0f };    // bottom left
    pos_vtx[1] = { 0.5f,  -0.5f, 0.0f };    // bottom right
    pos_vtx[2] = { -0.5f, 0.5f, 0.0f };    // top left
    pos_vtx[3] = { 0.5f, 0.5f, 0.0f };    // top right

    // color
    std::vector<glm::vec4> clr_vtx(4);
    clr_vtx[0] = { 0.0f, 0.0f, 0.0f, 0.0f };
    clr_vtx[1] = { 0.0f, 0.0f, 0.0f, 0.0f };
    clr_vtx[2] = { 0.0f, 0.0f, 0.0f, 0.0f };
    clr_vtx[3] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // texture
    std::vector<glm::vec2> uv_vtx(4);
    uv_vtx[0] = { 0.0f, 1.0f };     // top left
    uv_vtx[1] = { 1.0f, 1.0f };     // top right
    uv_vtx[2] = { 0.0f, 0.0f };     // bottom left
    uv_vtx[3] = { 1.0f, 0.0f };     // bottom right

    // normal
    //std::vector<glm::vec3> normal_vtx(4);
    //normal_vtx[0] = { 0.0f, 0.0f, 1.0f };
    //normal_vtx[1] = { 0.0f, 0.0f, 1.0f };
    //normal_vtx[2] = { 0.0f, 0.0f, 1.0f };
    //normal_vtx[3] = { 0.0f, 0.0f, 1.0f };

    // topology
    std::vector<GLshort> idx_vtx(6);
    idx_vtx[0] = 0;
    idx_vtx[1] = 1;
    idx_vtx[2] = 2;
    idx_vtx[3] = 2;
    idx_vtx[4] = 1;
    idx_vtx[5] = 3;

    return setup_vao_rect(pos_vtx, clr_vtx, uv_vtx, idx_vtx);
}

std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::setup_vao_rect(
  const std::vector<glm::vec3>& pos_vtx,
  const std::vector<glm::vec4>& clr_vtx,
  const std::vector<glm::vec2>& uv_vtx,
  std::vector <GLshort>& idx_vtx)
{
  GLuint vaoid;
  GLuint vbo_posclruv;

  glCreateBuffers(1, &vbo_posclruv);

  // allocate storage pos/color
  glNamedBufferStorage(vbo_posclruv,
    sizeof(glm::vec3) * pos_vtx.size() +
    sizeof(glm::vec4) * clr_vtx.size() +
    sizeof(glm::vec2) * uv_vtx.size(),
    nullptr,
    GL_DYNAMIC_STORAGE_BIT);

  glNamedBufferSubData(vbo_posclruv,
    0,                                  // offset
    sizeof(glm::vec3) * pos_vtx.size(), // space
    pos_vtx.data());                    // actual data
  glNamedBufferSubData(vbo_posclruv,
    sizeof(glm::vec3) * pos_vtx.size(), // offset
    sizeof(glm::vec4) * clr_vtx.size(), // space
    clr_vtx.data());                    // actual data
  glNamedBufferSubData(vbo_posclruv,
    sizeof(glm::vec3) * pos_vtx.size() + sizeof(glm::vec4) * clr_vtx.size(), // offset
    sizeof(glm::vec2) * uv_vtx.size(),                                       // space
    uv_vtx.data());                                                          // actual data

  glCreateVertexArrays(1, &vaoid);

  // position
  glEnableVertexArrayAttrib(vaoid, 0);
  glVertexArrayVertexBuffer(vaoid, 0, vbo_posclruv,
    0,
    sizeof(glm::vec3));
  glVertexArrayAttribFormat(vaoid, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoid, 0, 0);

  // color
  glEnableVertexArrayAttrib(vaoid, 1);
  glVertexArrayVertexBuffer(vaoid, 1, vbo_posclruv,
    sizeof(glm::vec3) * pos_vtx.size(),
    sizeof(glm::vec4));
  glVertexArrayAttribFormat(vaoid, 1, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoid, 1, 1);

  // texture
  glEnableVertexArrayAttrib(vaoid, 2);
  glVertexArrayVertexBuffer(vaoid, 2, vbo_posclruv,
    sizeof(glm::vec3) * pos_vtx.size() + sizeof(glm::vec4) * clr_vtx.size(),
    sizeof(glm::vec2));
  glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoid, 2, 2);

  // normal
  //glEnableVertexArrayAttrib(vaoid, 3);
  //glVertexArrayVertexBuffer(vaoid, 3, vbo_posclruv,
  //    sizeof(glm::vec3) * pos_vtx.size() + sizeof(glm::vec4) * clr_vtx.size() + sizeof(glm::vec2) * uv_vtx.size(),
  //    sizeof(glm::vec3));
  //glVertexArrayAttribFormat(vaoid, 3, 3, GL_FLOAT, GL_FALSE, 0);
  //glVertexArrayAttribBinding(vaoid, 3, 3);

  GLuint ebo_hdl;
  glCreateBuffers(1, &ebo_hdl);
  glNamedBufferStorage(ebo_hdl,
    sizeof(GLushort) * idx_vtx.size(),
    reinterpret_cast<GLvoid*>(idx_vtx.data()),
    GL_DYNAMIC_STORAGE_BIT);

  glVertexArrayElementBuffer(vaoid, ebo_hdl);

  // update total number of indices
  GLuint idx_cnt = static_cast<GLuint>(idx_vtx.size()); // render 2 triangles = 6 indices
  return std::make_tuple(GL_TRIANGLES, vaoid, idx_cnt);
}

std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::getLineMesh()
{
  static bool lineMade;
  static std::tuple<GLenum, GLuint, GLuint> primitiveType_vaoid_idxcnt;

  if (!lineMade)
  {
    // positions
    std::array<glm::vec3, 2> pos_vtx;
    pos_vtx[0] = { -0.5, 0, 0 };
    pos_vtx[1] = { 0.5, 0, 0 };

    // topology
    std::array<GLshort, 2> idx_vtx;
    idx_vtx[0] = 0;
    idx_vtx[1] = 1;

    std::array<glm::vec2, 2> tex_vtx;
    tex_vtx[0] = { 0, 0 };
    tex_vtx[1] = { 0, 1 };

    primitiveType_vaoid_idxcnt = UWUEngine::Mesh::setup_vao_line(pos_vtx, idx_vtx, tex_vtx);
    lineMade = true;
  }

  return primitiveType_vaoid_idxcnt;
}

std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::getCustomMesh(const std::vector<glm::vec3>& pos_vtx,
  const std::vector<glm::vec4>& clr_vtx, const std::vector<glm::vec2>& uv_vtx,
  std::vector<GLshort>& idx_vtx)
{
  std::tuple<GLenum, GLuint, GLuint> mesh = UWUEngine::Mesh::setup_vao_rect(pos_vtx, clr_vtx, uv_vtx, idx_vtx);
  return mesh;
}

std::tuple<GLenum, GLuint, GLuint> UWUEngine::Mesh::setup_vao_line(
  const std::array<glm::vec3, 2>& pos_vtx,
  std::array <GLshort, 2>& idx_vtx, const std::array<glm::vec2, 2>& tex_vtx)
{
  GLuint vbo_line;
  glCreateBuffers(1, &vbo_line);
  glNamedBufferStorage(vbo_line,
    sizeof(glm::vec3) * pos_vtx.size() + sizeof(glm::vec2) * tex_vtx.size(), nullptr,
    GL_DYNAMIC_STORAGE_BIT);
  glNamedBufferSubData(vbo_line, 0,
    sizeof(glm::vec3) * pos_vtx.size(), pos_vtx.data());
  glNamedBufferSubData(vbo_line, sizeof(glm::vec3) * pos_vtx.size(),
    sizeof(glm::vec2) * tex_vtx.size(), tex_vtx.data());

  GLuint vaoid_line;
  glCreateVertexArrays(1, &vaoid_line);
  glEnableVertexArrayAttrib(vaoid_line, 0);
  glVertexArrayVertexBuffer(vaoid_line, 0, vbo_line, 0, sizeof(glm::vec3));
  glVertexArrayAttribFormat(vaoid_line, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoid_line, 0, 0);

  glEnableVertexArrayAttrib(vaoid_line, 2);
  glVertexArrayVertexBuffer(vaoid_line, 2, vbo_line, sizeof(glm::vec3) * pos_vtx.size(), sizeof(glm::vec2));
  glVertexArrayAttribFormat(vaoid_line, 2, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoid_line, 2, 2);

  GLuint ebo_hdl;
  glCreateBuffers(1, &ebo_hdl);
  glNamedBufferStorage(ebo_hdl,
    sizeof(GLushort) * idx_vtx.size(),
    reinterpret_cast<GLvoid*>(idx_vtx.data()),
    GL_DYNAMIC_STORAGE_BIT);

  glVertexArrayElementBuffer(vaoid_line, ebo_hdl);

  GLuint idx_cnt_line = static_cast<GLuint>(idx_vtx.size());

  return std::make_tuple(GL_LINES, vaoid_line, idx_cnt_line);
}
