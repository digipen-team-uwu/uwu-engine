#include <UWUEngine/Modules/InstancingMod.h>
#include <UWUEngine/Modules/VAOMod.h>
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

InstancingMod::InstancingMod(ISpace* space) : System(space)
{
  CreateInstances(Get<VAOMod>().GetVAOEnvironment(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  CreateInstances(Get<VAOMod>().GetVAODebug(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  CreateInstances(Get<VAOMod>().GetVAOParticle(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  CreateInstances(Get<VAOMod>().GetVAOUI(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  CreateInstances(Get<VAOMod>().GetVAOLight(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayScale(),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &Get<CompSpaceSys>().space_light.Get<LightComp>().GetArrayShininess()
  );
}

InstancingMod::~InstancingMod()
{
  DeleteInstances();
}

void InstancingMod::Update()
{
  UpdateInstances(Get<VAOMod>().GetVAOEnvironment(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_environment.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_environment.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  UpdateInstances(Get<VAOMod>().GetVAODebug(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_debug.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_debug.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  UpdateInstances(Get<VAOMod>().GetVAOParticle(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_particle.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_particle.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  UpdateInstances(Get<VAOMod>().GetVAOUI(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_ui.Get<TransformComp>().GetArrayScale(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayColors(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayUVS(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayDimensions(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasUV(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasScale(),
    &Get<CompSpaceSys>().space_ui.Get<TextureComp>().GetArrayAtlasLayers(),
    NULL
  );
  UpdateInstances(Get<VAOMod>().GetVAOLight(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayRotation(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayTranslation(),
    &Get<CompSpaceSys>().space_light.Get<TransformComp>().GetArrayScale(),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &Get<CompSpaceSys>().space_light.Get<LightComp>().GetArrayShininess()
  );
}

void InstancingMod::CreateInstances(const GLuint& vao,
  const std::vector<float>* rotation,
  const std::vector<glm::vec4>* translation,
  const std::vector<glm::vec3>* scale,
  const std::vector<glm::vec4>* color,
  const std::vector<glm::vec2>* uvs,
  const std::vector<glm::uvec2>* dimension,
  const std::vector<glm::vec2>* atlas_uv_,
  const std::vector<glm::vec2>* atlas_scale_,
  const std::vector<unsigned>* atlas_layer_,
  const std::vector<float>* material_shininess_)
{
  if (rotation)
  {
    CreateInstancedVBO(vao, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
      rotation->data(), 4, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (translation)
  {
    CreateInstancedVBO(vao, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
      translation->data(), 5, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (scale)
  {
    CreateInstancedVBO(vao, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
      scale->data(), 6, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (color)
  {
    CreateInstancedVBO(vao, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
      color->data(), 7, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (uvs)
  {
    CreateInstancedVBO(vao, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
      uvs->data(), 8, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (dimension)
  {
    CreateInstancedVBO(vao, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
      dimension->data(), 9, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (atlas_uv_)
  {
    CreateInstancedVBO(vao, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
      atlas_uv_->data(), 10, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (atlas_scale_)
  {
    CreateInstancedVBO(vao, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
      atlas_scale_->data(), 11, GL_ELEMENT_ARRAY_BUFFER);
  }
  
  if (atlas_layer_)
  {
    CreateInstancedVBO(vao, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
      atlas_layer_->data(), 12, GL_ELEMENT_ARRAY_BUFFER);
  }

  if (material_shininess_)
  {
    CreateInstancedVBO(vao, Shininess, sizeof(float) * static_cast<unsigned>(material_shininess_->capacity()),
      material_shininess_->data(), 13, GL_ELEMENT_ARRAY_BUFFER);
  }
}

void InstancingMod::CreateInstancedVBO(
  const GLuint& vao, 
  InstanceData name, 
  unsigned size, 
  const void* data, 
  unsigned location,
  GLenum bufferType)
{
  GLuint vbo;
  glCreateBuffers(1, &vbo);
  glBindBuffer(bufferType, vbo);
  glNamedBufferStorage(vbo, size, nullptr,
    GL_DYNAMIC_STORAGE_BIT);
  // write data to buffer (reuse allocated memory which is god)
  glNamedBufferSubData(vbo, 0, size, data);
  glEnableVertexArrayAttrib(vao, location);
  if (name == Rotation)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(float));

    glVertexArrayAttribFormat(vao, location, 1, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == Translation)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec4));
    glVertexArrayAttribFormat(vao, location, 4, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == Scale)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec3));
    glVertexArrayAttribFormat(vao, location, 3, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == Colors)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec4));
    glVertexArrayAttribFormat(vao, location, 4, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == UVOffset)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(vao, location, 2, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == UVScale)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::uvec2));
    glVertexArrayAttribFormat(vao, location, 2, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == AtlasUV)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(vao, location, 2, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == AtlasScale)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(vao, location, 2, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == AtlasLayer)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(unsigned));
    glVertexArrayAttribFormat(vao, location, 1, GL_FLOAT, GL_FALSE, 0);
  }
  else if (name == Shininess)
  {
    glVertexArrayVertexBuffer(vao, location, vbo, 0, sizeof(float));
    glVertexArrayAttribFormat(vao, location, 1, GL_FLOAT, GL_FALSE, 0);
  }

  glVertexArrayAttribBinding(vao, location, location);

  glVertexArrayBindingDivisor(vao, location, 1);
  vbos[vao] = vbo;
}

void InstancingMod::UpdateInstances(const GLuint& vao,
  const std::vector<float>* rotation, 
  const std::vector<glm::vec4>* translation,
  const std::vector<glm::vec3>* scale, 
  const std::vector<glm::vec4>* color, 
  const std::vector<glm::vec2>* uvs, 
  const std::vector<glm::uvec2>* dimension, 
  const std::vector<glm::vec2>* atlas_uv_, 
  const std::vector<glm::vec2>* atlas_scale_, 
  const std::vector<unsigned>* atlas_layer_, 
  const std::vector<float>* material_shininess_)
{
  if (rotation)
  {
    UpdateInstancedVBO(vao, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
      rotation->data());
  }
  
  if (translation)
  {
    UpdateInstancedVBO(vao, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
      translation->data());
  }
  
  if (scale)
  {
    UpdateInstancedVBO(vao, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
      scale->data());
  }
  
  if (color)
  {
    UpdateInstancedVBO(vao, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
      color->data());
  }
  
  if (uvs)
  {
    UpdateInstancedVBO(vao, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
      uvs->data());
  }
  
  if (dimension)
  {
    UpdateInstancedVBO(vao, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
      dimension->data());
  }
  
  if (atlas_uv_)
  {
    UpdateInstancedVBO(vao, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
      atlas_uv_->data());
  }
  
  if (atlas_scale_)
  {
    UpdateInstancedVBO(vao, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
      atlas_scale_->data());
  }
  
  if (atlas_layer_)
  {
    UpdateInstancedVBO(vao, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
      atlas_layer_->data());
  }
  
  if (material_shininess_)
  {
    UpdateInstancedVBO(vao, Shininess, sizeof(float) * static_cast<unsigned>(material_shininess_->capacity()),
      material_shininess_->data());
  }
}

void InstancingMod::UpdateInstancedVBO(const GLuint& vao, 
  InstanceData name, unsigned size, const void* data)
{
  // orphaning
  glInvalidateBufferData(vbos[vao]);

  // write data to buffer (reuse allocated memory which is god)
  glNamedBufferSubData(vbos[vao], 0, size, data);

  /*auto destination = glMapNamedBuffer(vbo, GL_WRITE_ONLY);
  memcpy(destination, data, size);
  glUnmapNamedBuffer(vbo);*/
}

void InstancingMod::DeleteInstances()
{
  for (auto& i : vbos)
  {
    glDeleteBuffers(1, &i.second);
  }
}
