#pragma once
#include <UWUEngine/BaseSystem.h>
#include <vector>
#include <glm/glm.hpp>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <UWUEngine/Instances.h>
#include <UWUEngine/Instances.h>

class UIManager : public BaseSystem<UIManager>
{
public:
  UIManager();
  void Update() override;
  static void Render();


  static const glm::mat4& GetProjection();
  static const glm::mat4& GetView();

  //static void ResizeBufferIfNecessary();
  static void PushElement(float rotation, const glm::vec4& location, const glm::vec3& scale, const glm::vec4& color, const glm::vec2& uvs, const glm::uvec2& dimensions, const glm::vec2& atlasUV, const glm::vec2& atlasScale, unsigned atlasLayer);
private:
  static VaoKey UIKey;
  static std::tuple<GLenum, GLuint, GLuint> uiMesh;
  static std::vector<float> rotation;
  static std::vector<glm::vec4> translation;
  static std::vector<glm::vec3> scale;
  static std::vector<glm::vec4> color;
  static std::vector<glm::vec2> uvs;
  static std::vector<glm::uvec2> dims;
  static std::vector<glm::vec2> atlasUVs;
  static std::vector<glm::vec2> atlasScale;
  static std::vector<unsigned> atlasLayer;
  static size_t bufferSize;
  static glm::mat4 projection;
  static glm::mat4 view;
};
