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
#include <UWUEngine/Instances.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <UWUEngine/Component/LightingComponentManager.h>
#include "UWUEngine/Graphics/Texture/AtlasModule.h"

std::vector<GLuint> Instances::vaos;
std::unordered_map<VaoKey, std::array<GLuint, Instances::InstanceData::Total>> Instances::vbos;
VaoKey Instances::entity_vao_key;

Instances::~Instances()
{
    DeleteInstances();
}

void Instances::SetNULLsToEntities(const std::vector<float>*& rotation,
  const std::vector<glm::vec4>*& translation,
  const std::vector<glm::vec3>*& scale,
  const std::vector<glm::vec4>*& color,
  const std::vector<glm::vec2>*& uvs,
  const std::vector<glm::uvec2>*& dimension,
  const std::vector<glm::vec2>*& atlas_uv_,
  const std::vector<glm::vec2>*& atlas_scale_,
  const std::vector<unsigned>*& atlas_layer_,
    const std::vector<float>*& material_shininess_)
{
  if (!rotation)
  {
    rotation = &TransformComponentManager::GetArrayRotation();
  }
  if (!translation)
  {
    translation = &TransformComponentManager::GetArrayTranslation();
  }
  if (!scale)
  {
    scale = &TransformComponentManager::GetArrayScale();
  }
  if (!color)
  {
    color = &TextureComponentManager::GetArrayColors();
  }
  if (!uvs)
  {
    uvs = &TextureComponentManager::GetArrayUVS();
  }
  if (!dimension)
  {
    dimension = &TextureComponentManager::GetArrayDimensions();
  }
  if (!atlas_uv_)
  {
    atlas_uv_ = &TextureAtlaser::GetArrayAtlasUV();
  }
  if (!atlas_scale_)
  {
    atlas_scale_ = &TextureAtlaser::GetArrayAtlasScale();
  }
  if (!atlas_layer_)
  {
    atlas_layer_ = &TextureAtlaser::GetArrayAtlasLayer();
  }
    if (!material_shininess_)
    {
        material_shininess_ = &LightingComponentManager::GetArrayShininess();
    }
}

void Instances::SetNULLsToEntitiesHUD(const std::vector<float>*& rotation, const std::vector<glm::vec4>*& translation, const std::vector<glm::vec3>*& scale, const std::vector<glm::vec4>*& color, const std::vector<glm::vec2>*& uvs, const std::vector<glm::uvec2>*& dimension, const std::vector<glm::vec2>*& atlas_uv_, const std::vector<glm::vec2>*& atlas_scale_, const std::vector<unsigned>*& atlas_layer_)
{
    if (!rotation)
    {
        rotation = &TransformComponentManager::GetArrayRotation();
    }
    if (!translation)
    {
        translation = &TransformComponentManager::GetArrayTranslation();
    }
    if (!scale)
    {
        scale = &TransformComponentManager::GetArrayScale();
    }
    if (!color)
    {
        color = &TextureComponentManager::GetArrayColors();
    }
    if (!uvs)
    {
        uvs = &TextureComponentManager::GetArrayUVS();
    }
    if (!dimension)
    {
        dimension = &TextureComponentManager::GetArrayDimensions();
    }
    if (!atlas_uv_)
    {
        atlas_uv_ = &TextureAtlaser::GetArrayAtlasUV();
    }
    if (!atlas_scale_)
    {
        atlas_scale_ = &TextureAtlaser::GetArrayAtlasScale();
    }
    if (!atlas_layer_)
    {
        atlas_layer_ = &TextureAtlaser::GetArrayAtlasLayer();
    }
}

VaoKey Instances::CreateInstancesHUD(const std::tuple<GLenum, GLuint, GLuint>& mesh, GLenum bufferType,
    const std::vector<float>* rotation,
    const std::vector<glm::vec4>* translation,
    const std::vector<glm::vec3>* scale,
    const std::vector<glm::vec4>* color,
    const std::vector<glm::vec2>* uvs,
    const std::vector<glm::uvec2>* dimension,
    const std::vector<glm::vec2>* atlas_uv_,
    const std::vector<glm::vec2>* atlas_scale_,
    const std::vector<unsigned>* atlas_layer_)
{
    auto vaoid = std::get<1>(mesh);
    bool duplicate = false;
    VaoKey vao_key = 0;

    // caching vaoid
    for (auto it : vaos)
    {
        if (it == vaoid)
        {
            duplicate = true;
            break;
        }
        ++vao_key;
    }

    if (!duplicate)
    {
        vaos.push_back(vaoid);
        vao_key = vaos.size() - 1;
    }
    SetNULLsToEntitiesHUD(rotation, translation, scale, color, uvs, dimension, atlas_uv_, atlas_scale_, atlas_layer_);
    CreateInstancedVBO(vao_key, vaoid, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
        rotation->data(), 4, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
        translation->data(), 5, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
        scale->data(), 6, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
        color->data(), 7, bufferType);

    CreateInstancedVBO(vao_key, vaoid, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
        uvs->data(), 8, bufferType);

    CreateInstancedVBO(vao_key, vaoid, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
        dimension->data(), 9, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
        atlas_uv_->data(), 10, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
        atlas_scale_->data(), 11, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
        atlas_layer_->data(), 12, bufferType);

    return vao_key;
}

VaoKey Instances::CreateInstances(const std::tuple<GLenum, GLuint, GLuint>& mesh, GLenum bufferType,
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
    auto vaoid = std::get<1>(mesh);
    bool duplicate = false;
    VaoKey vao_key = 0;

    // caching vaoid
    for (auto it : vaos)
    {  
      if (it == vaoid)
      {
        duplicate = true;
        break;
      }
      ++vao_key;
    }

    if (!duplicate)
    {
      vaos.push_back(vaoid);
      vao_key = vaos.size() - 1;
    }

    SetNULLsToEntities(rotation, translation, scale, color, uvs, dimension, atlas_uv_, 
        atlas_scale_, atlas_layer_, material_shininess_);

    CreateInstancedVBO(vao_key, vaoid, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
        rotation->data(), 4, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
        translation->data(), 5, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
        scale->data(), 6, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
        color->data(), 7, bufferType);

    CreateInstancedVBO(vao_key, vaoid, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
        uvs->data(), 8, bufferType);

    CreateInstancedVBO(vao_key, vaoid, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
        dimension->data(), 9, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
        atlas_uv_->data(), 10, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
        atlas_scale_->data(), 11, bufferType);

    CreateInstancedVBO(vao_key, vaoid, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
        atlas_layer_->data(), 12, bufferType);

    CreateInstancedVBO(vao_key, vaoid, Shininess, sizeof(float) * static_cast<unsigned>(material_shininess_->capacity()),
        material_shininess_->data(), 13, bufferType);

    return vao_key;
}

void Instances::CreateInstancedVBO(VaoKey vao_key, GLuint vao, InstanceData name, unsigned size, const void* data, unsigned location, GLenum bufferType)
{
    //OPENGL_ERR;
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

    vbos[vao_key][name] = vbo;
}

void Instances::UpdateInstances(VaoKey vao_key, const std::vector<float>* rotation,
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
    SetNULLsToEntities(rotation, translation, scale, color, uvs, dimension, 
        atlas_uv_, atlas_scale_, atlas_layer_, material_shininess_);

    UpdateInstancedVBO(vao_key, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
        rotation->data());

    UpdateInstancedVBO(vao_key, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
        translation->data());

    UpdateInstancedVBO(vao_key, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
        scale->data());

    UpdateInstancedVBO(vao_key, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
        color->data());

    UpdateInstancedVBO(vao_key, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
        uvs->data());

    UpdateInstancedVBO(vao_key, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
        dimension->data());

    UpdateInstancedVBO(vao_key, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
        atlas_uv_->data());

    UpdateInstancedVBO(vao_key, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
        atlas_scale_->data());

    UpdateInstancedVBO(vao_key, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
      atlas_layer_->data());

    UpdateInstancedVBO(vao_key, Shininess, sizeof(float) * static_cast<unsigned>(material_shininess_->capacity()),
        material_shininess_->data());
}

void Instances::UpdateInstancesHUD(VaoKey vao_key,
    const std::vector<float>* rotation,
    const std::vector<glm::vec4>* translation,
    const std::vector<glm::vec3>* scale,
    const std::vector<glm::vec4>* color,
    const std::vector<glm::vec2>* uvs,
    const std::vector<glm::uvec2>* dimension,
    const std::vector<glm::vec2>* atlas_uv_,
    const std::vector<glm::vec2>* atlas_scale_,
    const std::vector<unsigned>* atlas_layer_)
{
    SetNULLsToEntitiesHUD(rotation, translation, scale, color, uvs, dimension, atlas_uv_, atlas_scale_, atlas_layer_);
    UpdateInstancedVBO(vao_key, Rotation, sizeof(float) * static_cast<unsigned>(rotation->capacity()),
        rotation->data());

    UpdateInstancedVBO(vao_key, Translation, sizeof(glm::vec4) * static_cast<unsigned>(translation->capacity()),
        translation->data());

    UpdateInstancedVBO(vao_key, Scale, sizeof(glm::vec3) * static_cast<unsigned>(scale->capacity()),
        scale->data());

    UpdateInstancedVBO(vao_key, Colors, sizeof(glm::vec4) * static_cast<unsigned>(color->capacity()),
        color->data());

    UpdateInstancedVBO(vao_key, UVOffset, sizeof(glm::vec2) * static_cast<unsigned>(uvs->capacity()),
        uvs->data());

    UpdateInstancedVBO(vao_key, UVScale, sizeof(glm::uvec2) * static_cast<unsigned>(dimension->capacity()),
        dimension->data());

    UpdateInstancedVBO(vao_key, AtlasUV, sizeof(glm::vec2) * static_cast<unsigned>(atlas_uv_->capacity()),
        atlas_uv_->data());

    UpdateInstancedVBO(vao_key, AtlasScale, sizeof(glm::vec2) * static_cast<unsigned>(atlas_scale_->capacity()),
        atlas_scale_->data());

    UpdateInstancedVBO(vao_key, AtlasLayer, sizeof(unsigned) * static_cast<unsigned>(atlas_layer_->capacity()),
        atlas_layer_->data());
}

void Instances::UpdateInstancedVBO(VaoKey vao_key, InstanceData name, unsigned size, const void* data)
{
    GLuint vbo = vbos[vao_key][name];

    // orphaning
    glInvalidateBufferData(vbo);

    // write data to buffer (reuse allocated memory which is god)
    glNamedBufferSubData(vbo, 0, size, data);
    
    /*auto destination = glMapNamedBuffer(vbo, GL_WRITE_ONLY);
    memcpy(destination, data, size);
    glUnmapNamedBuffer(vbo);*/
}

void Instances::DeleteInstances()
{
}

const GLuint Instances::GetVAOid(VaoKey vao_key)
{
    return vaos[vao_key];
}

const std::array<GLuint, Instances::InstanceData::Total>& Instances::GetArrayVBOs(VaoKey vao_key)
{
    return vbos[vao_key];
}

void Instances::SetEntityVAOKey(VaoKey new_vao_key)
{
    entity_vao_key = new_vao_key;
}

const VaoKey Instances::GetEntityVAOKey()
{
    return entity_vao_key;
}

