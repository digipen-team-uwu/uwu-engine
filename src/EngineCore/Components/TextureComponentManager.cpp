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
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/constants.h>
#include <string>
#include <fstream>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Serialization.h>
#include "UWUEngine/Graphics/Texture/AtlasModule.h"

namespace goc = GameObjectConstants;
using namespace UWUEngine;

Texture TextureComp::operator[](EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], textureID_[ID], filePaths_[ID]);
}

UWUEngine::Texture TextureComp::getTexture(EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], textureID_[ID], filePaths_[ID]);
}

void TextureComp::InitObject(EntityID ID)
{
  dimensions_[ID] = { 1, 1 };
  uvs_[ID] = { 0, 0 };
  colors_[ID] = { 1, 1, 1, 1 };
}

TextureComp::~TextureComp()
{
  for (auto i : EntitySys::GetIDs())
  {
    glDeleteTextures(1, &textureID_[i]);
  }
}

void TextureComp::RemoveColor(EntityID ID)
{
  Texture texture = getTexture(ID);
  texture.SetColors(glm::vec4(1.0f));
}

void TextureComp::ShutdownObject(EntityID ID)
{
  uvs_[ID] = { -1,-1 };
}

bool TextureComp::HasFilepath(EntityID ID)
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

const std::string& TextureComp::getFilePath(EntityID ID, unsigned accessID)
{
  Texture texture = getTexture(ID);
  return texture.GetFilePaths(accessID);
}

void TextureComp::SetFilePath(EntityID ID, const char *filePath, unsigned accessID)
{
  Texture texture = getTexture(ID);
  texture.SetFilePath(std::string(filePath), accessID);
  AtlasModule::SetAtlasData(ID);
}

void TextureComp::SetCurrentTexture(EntityID ID, unsigned accessID)
{
  AtlasModule::SetAtlasData(ID, accessID);
}

void TextureComp::SetFilePaths(EntityID ID, const std::array<std::string, goc::MAX_SPRITES>& filePaths)
{
  filePaths_[ID] = filePaths;
  AtlasModule::SetAtlasData(ID);
}

void TextureComp::Serialize(std::ofstream& stream, EntityID id)
{
  stream << "\"texture\" :\n";
  stream << Tabs::TWO << "{\n";

  if (TextureComp::HasFilepath(id))
  {
    stream << Tabs::THREE << R"("filepath" : ")" << TextureComp::getFilePath(id) << '"';
    stream << ",\n";
  }

  SerializeVec4(stream, "color", colors_[id]);
  stream << ",\n";

  SerializeVec2(stream, "uvs", uvs_[id]);

  stream << Tabs::THREE << "}";
}

#pragma region Array Getter
const EntityVector<glm::uvec2>& TextureComp::GetArrayDimensions() const
{
    return dimensions_;
}

const EntityVector<glm::vec2>& TextureComp::GetArrayUVS() const
{
    return uvs_;
}

const EntityVector<glm::vec4>& TextureComp::GetArrayColors() const
{
    return colors_;
}

const std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>>& TextureComp::GetArrayFilePaths() const
{
    return filePaths_;
}
#pragma endregion 
