/******************************************************************************/
/*!
\par        Project Umbra
\file       Instances.h
\author     Chau Nguyen
\date       2019/11/1
\brief      Managing Vertex Buffer Object

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <GL/glew.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <unordered_map>
#include <UWUEngine/BaseSystem.h>

using VaoKey = size_t;

class Instances : public BaseSystem<Instances>
{
public:
  Instances();
  ~Instances();

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
    //LightState,

    Ambient,
    Diffuse,
    Specular,
    Shininess,

    Total
  };

  static VaoKey CreateInstancesHUD(const std::tuple<GLenum, GLuint, GLuint>& mesh, GLenum bufferType = GL_ELEMENT_ARRAY_BUFFER,
      const std::vector<float>* rotation = NULL,
      const std::vector<glm::vec4>* translation = NULL,
      const std::vector<glm::vec3>* scale = NULL,
      const std::vector<glm::vec4>* color = NULL,
      const std::vector<glm::vec2>* uvs = NULL,
      const std::vector<glm::uvec2>* dimension = NULL,
      const std::vector<glm::vec2>* atlas_uv_ = NULL,
      const std::vector<glm::vec2>* atlas_scale_ = NULL,
      const std::vector<unsigned>* atlas_layer_ = NULL);

  static VaoKey CreateInstances(const std::tuple<GLenum, GLuint, GLuint>& mesh, GLenum bufferType = GL_ELEMENT_ARRAY_BUFFER,
    const std::vector<float>* rotation = NULL,
    const std::vector<glm::vec4>* translation = NULL,
    const std::vector<glm::vec3>* scale = NULL,
    const std::vector<glm::vec4>* color = NULL,
    const std::vector<glm::vec2>* uvs = NULL,
    const std::vector<glm::uvec2>* dimension = NULL,
    const std::vector<glm::vec2>* atlas_uv_ = NULL,
    const std::vector<glm::vec2>* atlas_scale_ = NULL,
    const std::vector<unsigned>* atlas_layer_ = NULL,
    const std::vector<glm::vec3>* material_ambient_ = NULL,
    const std::vector<glm::vec3>* material_diffuse_= NULL,
    const std::vector<glm::vec3>* material_specular_ = NULL,
    const std::vector<float>* material_shininess_= NULL);

  static void CreateInstancedVBO(VaoKey vao_key, GLuint vao, InstanceData name, unsigned size, const void* data, unsigned location, GLenum bufferType);

  static void UpdateInstances(VaoKey vao_key, const std::vector<float>* rotation = NULL,
    const std::vector<glm::vec4>* translation = NULL,
    const std::vector<glm::vec3>* scale = NULL,
    const std::vector<glm::vec4>* color = NULL,
    const std::vector<glm::vec2>* uvs = NULL,
    const std::vector<glm::uvec2>* dimension = NULL,
    const std::vector<glm::vec2>* atlas_uv_ = NULL,
    const std::vector<glm::vec2>* atlas_scale_ = NULL,
    const std::vector<unsigned>* atlas_layer_ = NULL,
    const std::vector<int>* light_state = NULL,
    const std::vector<glm::vec3>* material_ambient_ = NULL,
    const std::vector<glm::vec3>* material_diffuse_ = NULL,
    const std::vector<glm::vec3>* material_specular_ = NULL,
    const std::vector<float>* material_shininess_ = NULL);

  static void UpdateInstancesHUD(VaoKey vao_key, const std::vector<float>* rotation = NULL,
      const std::vector<glm::vec4>* translation = NULL,
      const std::vector<glm::vec3>* scale = NULL,
      const std::vector<glm::vec4>* color = NULL,
      const std::vector<glm::vec2>* uvs = NULL,
      const std::vector<glm::uvec2>* dimension = NULL,
      const std::vector<glm::vec2>* atlas_uv_ = NULL,
      const std::vector<glm::vec2>* atlas_scale_ = NULL,
      const std::vector<unsigned>* atlas_layer_ = NULL);

  static void UpdateInstancedVBO(VaoKey vao_key, InstanceData name, unsigned size, const void* data);
  static void DeleteInstances();

  static const GLuint GetVAOid(VaoKey vao_key);

  static const std::array<GLuint, InstanceData::Total>& GetArrayVBOs(VaoKey vao_key);

  static void SetEntityVAOKey(VaoKey new_vao_key);
  static const VaoKey GetEntityVAOKey();

private:
  // a vector of vao id that use vao key to index in
  static std::vector<GLuint> vaos;

  // a map that has vao key to access into array of vbos
  static std::unordered_map<VaoKey, std::array<GLuint, InstanceData::Total>> vbos;

  static VaoKey entity_vao_key;
  // a vector of vao keys that use entityID to index in
  //EntityVector<VaoKey> vao_keys{ GameObjectConstants::INITIAL_OBJECT_COUNT };

  static void SetNULLsToEntities(const std::vector<float>*& rotation,
      const std::vector<glm::vec4>*& translation,
      const std::vector<glm::vec3>*& scale,
      const std::vector<glm::vec4>*& color,
      const std::vector<glm::vec2>*& uvs,
      const std::vector<glm::uvec2>*& dimension,
      const std::vector<glm::vec2>*& atlas_uv_,
      const std::vector<glm::vec2>*& atlas_scale_,
      const std::vector<unsigned>*& atlas_layer_,
      const std::vector<glm::vec3>*& material_ambient_,
      const std::vector<glm::vec3>*& material_diffuse_,
      const std::vector<glm::vec3>*& material_specular_,
      const std::vector<float>*& material_shininess_);

  static void SetNULLsToEntitiesHUD(const std::vector<float>*& rotation,
      const std::vector<glm::vec4>*& translation,
      const std::vector<glm::vec3>*& scale,
      const std::vector<glm::vec4>*& color,
      const std::vector<glm::vec2>*& uvs,
      const std::vector<glm::uvec2>*& dimension,
      const std::vector<glm::vec2>*& atlas_uv_,
      const std::vector<glm::vec2>*& atlas_scale_,
      const std::vector<unsigned>*& atlas_layer_);
};
