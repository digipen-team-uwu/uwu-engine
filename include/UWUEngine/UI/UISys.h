#pragma once
#include <UWUEngine/System.h>
#include <vector>
#include <glm/glm.hpp>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <UWUEngine/Instances.h>

namespace UWUEngine
{

class UISys : public System
{
public:
  UISys(ISpace*);
  void Update() override;
  void Render();


  const glm::mat4& GetProjection();
  const glm::mat4& GetView();

  //static void ResizeBufferIfNecessary();
  void PushElement(float rotation, const glm::vec4& location, const glm::vec3& scale, const glm::vec4& color, const glm::vec2& uvs, const glm::uvec2& dimensions, const glm::vec2& atlasUV, const glm::vec2& atlasScale, unsigned atlasLayer);
private:
  VaoKey UIKey;
  std::tuple<GLenum, GLuint, GLuint> uiMesh;
  std::vector<float> rotation;
  std::vector<glm::vec4> translation;
  std::vector<glm::vec3> scale;
  std::vector<glm::vec4> color;
  std::vector<glm::vec2> uvs;
  std::vector<glm::uvec2> dims;
  std::vector<glm::vec2> atlasUVs;
  std::vector<glm::vec2> atlasScale;
  std::vector<unsigned> atlasLayer;
  size_t bufferSize;
  glm::mat4 projection;
  glm::mat4 view;
};

} // namespace UWUEngine
