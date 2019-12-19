#pragma once
#include <UWUEngine/BaseSystem.h>
#include <vector>
#include <glm/glm.hpp>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Instances.h>
class DebugManager : public BaseSystem<DebugManager>
{
public:
  DebugManager();
  void Update() override;
  static void Render();
  ~DebugManager() = default;
  
  static void EnableVelocityVectors();
  static void DisableVelocityVectors();
  static void EnableHitboxes();
  static void DisableHitboxes();
private:
  static VaoKey vectorVAO;
  static VaoKey hitboxVAO;
  static bool drawVectors;
  static bool drawHitboxes;
  static std::tuple<GLenum, GLuint, GLuint> lineMesh;
  static std::tuple<GLenum, GLuint, GLuint> squareMesh;

      /* instanced data */
  static std::vector<float> rotation;
  static std::vector<glm::vec4> translation;
  static std::vector<glm::vec3> scale;
  static std::vector<glm::vec4> color;
  static std::vector<glm::vec2> uvs;
  static std::vector<glm::uvec2> dims;
  static std::vector<glm::vec2> atlasUVs;
  static std::vector<glm::vec2> atlasScale;
  static std::vector<unsigned> atlasLayer;

};
