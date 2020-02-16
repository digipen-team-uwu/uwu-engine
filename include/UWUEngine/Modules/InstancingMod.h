#pragma once

#include <UWUEngine/System.h>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <unordered_map>

using VAOID = GLuint;
using VBOID = GLuint;

namespace UWUEngine
{
  class InstancingMod : public System
  {
  public:
    InstancingMod(ISpace* space);
    ~InstancingMod() override;
    void Update() override;

    enum InstanceData
    {
      INVALID = -1,
      Translation,
      Rotation,
      Scale,
      Colors,
      UVOffset,
      UVScale,
      AtlasUV,
      AtlasScale,
      AtlasLayer,
      Shininess,

      Total
    };

    void CreateInstances(const GLuint& vao,
      const std::vector<float>* rotation = NULL,
      const std::vector<glm::vec4>* translation = NULL,
      const std::vector<glm::vec3>* scale = NULL,
      const std::vector<glm::vec4>* color = NULL,
      const std::vector<glm::vec2>* uvs = NULL,
      const std::vector<glm::uvec2>* dimension = NULL,
      const std::vector<glm::vec2>* atlas_uv_ = NULL,
      const std::vector<glm::vec2>* atlas_scale_ = NULL,
      const std::vector<unsigned>* atlas_layer_ = NULL,
      const std::vector<float>* material_shininess_ = NULL);

    void CreateInstancedVBO(const GLuint& vao, 
      InstanceData name, unsigned size, const void* data, 
      unsigned location, GLenum bufferType);

    void UpdateInstances(const GLuint& vao,
      const std::vector<float>* rotation = NULL,
      const std::vector<glm::vec4>* translation = NULL,
      const std::vector<glm::vec3>* scale = NULL,
      const std::vector<glm::vec4>* color = NULL,
      const std::vector<glm::vec2>* uvs = NULL,
      const std::vector<glm::uvec2>* dimension = NULL,
      const std::vector<glm::vec2>* atlas_uv_ = NULL,
      const std::vector<glm::vec2>* atlas_scale_ = NULL,
      const std::vector<unsigned>* atlas_layer_ = NULL,
      const std::vector<float>* material_shininess_ = NULL);

    void UpdateInstancedVBO(const GLuint& vao, 
      InstanceData name, unsigned size, const void* data);

    void DeleteInstances();

  private:
    // a map that has vao key to access into array of vbos
    std::unordered_map<VAOID, VBOID> vbos;
  };
}