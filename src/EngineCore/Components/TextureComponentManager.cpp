/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureComponentManager.cpp
\author     Chau Nguyen
\date       2019/09/20
\brief      Managing textures

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/constants.h>
#include <string>
#include <fstream>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Serialization.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"

namespace goc = GameObjectConstants;
using namespace UWUEngine;

Texture TextureComponentManager::operator[](EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], textureID_[ID], filePaths_[ID]);
}

UWUEngine::Texture TextureComponentManager::getTexture(EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], textureID_[ID], filePaths_[ID]);
}

void TextureComponentManager::InitObject(EntityID ID)
{
  dimensions_[ID] = { 1, 1 };
  uvs_[ID] = { 0, 0 };
  colors_[ID] = { 1, 1, 1, 1 };
}

TextureComponentManager::~TextureComponentManager()
{
  for (auto i : EntityManager::GetIDs())
  {
    glDeleteTextures(1, &textureID_[i]);
  }
}

void TextureComponentManager::RemoveColor(EntityID ID)
{
  Texture texture = getTexture(ID);
  texture.SetColors(glm::vec4(1.0f));
}

void TextureComponentManager::ShutdownObject(EntityID ID)
{
  uvs_[ID] = { -1,-1 };
}

bool TextureComponentManager::HasFilepath(EntityID ID)
{
  return filePaths_.find(ID) != filePaths_.end();
}

#pragma region Setter
void Texture::SetDimension(const glm::uvec2& dimension)
{
    dimensions_ = dimension;
}

void Texture::SetTextureID(GLuint textureID)
{
    textureID_ = textureID;
}

void Texture::SetColors(const glm::vec4& colors)
{
  colors_ = colors;
}

void Texture::SetUVS(const glm::vec2& uvs)
{
  uvs_ = uvs;
}

void Texture::SetFilePath(const std::string& filePath, unsigned accessID)
{
  filePaths_[accessID] = filePath;
}

#pragma endregion 

#pragma region Getter
const glm::uvec2& Texture::GetDimension() const
{
    return dimensions_;
}

const GLuint& Texture::GetTextureID() const
{
    return textureID_;
}

 const glm::vec4& Texture::GetColors() const
{
    return colors_;
}

const glm::vec2& Texture::GetUVS() const
{
  return uvs_;
}

const std::string& Texture::GetFilePaths(unsigned accessID) const
{
  return filePaths_[accessID];
}

#pragma endregion 

const std::string& TextureComponentManager::getFilePath(EntityID ID, unsigned accessID)
{
  Texture texture = getTexture(ID);
  return texture.GetFilePaths(accessID);
}

void TextureComponentManager::SetFilePath(EntityID ID, const char *filePath, unsigned accessID)
{
  Texture texture = getTexture(ID);
  texture.SetFilePath(std::string(filePath), accessID);
  TextureAtlaser::SetAtlasData(ID);
}

void TextureComponentManager::SetCurrentTexture(EntityID ID, unsigned accessID)
{
  TextureAtlaser::SetAtlasData(ID, accessID);
}

void TextureComponentManager::SetFilePaths(EntityID ID, const std::array<std::string, goc::MAX_SPRITES>& filePaths)
{
  filePaths_[ID] = filePaths;
  TextureAtlaser::SetAtlasData(ID);
}

void TextureComponentManager::Serialize(std::ofstream& stream, EntityID id)
{
  stream << "\"texture\" :\n";
  stream << Tabs::TWO << "{\n";

  if (TextureComponentManager::HasFilepath(id))
  {
    stream << Tabs::THREE << R"("filepath" : ")" << TextureComponentManager::getFilePath(id) << '"';
    stream << ",\n";
  }

  SerializeVec4(stream, "color", colors_[id]);
  stream << ",\n";

  SerializeVec2(stream, "uvs", uvs_[id]);

  stream << Tabs::THREE << "}";
}

#pragma region Array Getter
const EntityVector<glm::uvec2>& TextureComponentManager::GetArrayDimensions() const
{
    return dimensions_;
}

const EntityVector<glm::vec2>& TextureComponentManager::GetArrayUVS() const
{
    return uvs_;
}

const EntityVector<glm::vec4>& TextureComponentManager::GetArrayColors() const
{
    return colors_;
}

const std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>>& TextureComponentManager::GetArrayFilePaths() const
{
    return filePaths_;
}
#pragma endregion 
