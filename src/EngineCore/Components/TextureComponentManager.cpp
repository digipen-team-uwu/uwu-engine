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

template<>
size_t RegisterComponentHelper<TextureComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<TextureComponentManager>(ComponentUpdateOrder::LAST);

namespace goc = GameObjectConstants;

EntityVector<glm::uvec2>     TextureComponentManager::dimensions_(goc::INITIAL_OBJECT_COUNT);
EntityVector<glm::vec2>      TextureComponentManager::uvs_(goc::INITIAL_OBJECT_COUNT, { -1, -1 });
EntityVector<glm::vec4>      TextureComponentManager::colors_(goc::INITIAL_OBJECT_COUNT);
EntityVector<GLuint>         TextureComponentManager::textureID_(goc::INITIAL_OBJECT_COUNT);
std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>> TextureComponentManager::filePaths_;


TextureComponentManager::TextureComponentManager()
{
    
}

TextureComponentManager::~TextureComponentManager()
{
  for (auto i : EntityManager::GetIDs())
  {
    glDeleteTextures(1, &textureID_[i]);
  }
}

void  TextureComponentManager::SetDimensions(const glm::uvec2& dimensions, EntityID id)
{
    dimensions_[id] = dimensions;
}

void TextureComponentManager::SetTextureID(EntityID ID, GLuint textureID)
{
    textureID_[ID] = textureID;
}

glm::uvec2& TextureComponentManager::GetDimensions(EntityID ID)
{
    return dimensions_[ID];
}

GLuint TextureComponentManager::GetTextureID(EntityID ID)
{
    return textureID_[ID];
}

void TextureComponentManager::InitObject(EntityID ID)
{
    dimensions_[ID] = { 1, 1 };
    uvs_[ID] = { 0, 0 };
    colors_[ID] = { 1, 1, 1, 1 };
}

void TextureComponentManager::SetColor(EntityID ID, const glm::vec4& newColor)
{
    colors_[ID] = newColor;
}

 glm::vec4& TextureComponentManager::GetColor(EntityID ID)
{
    return colors_[ID];
}

 void TextureComponentManager::RemoveColor(EntityID ID)
 {
     colors_[ID] = glm::vec4(1.0f);
 }

void TextureComponentManager::ShutdownObject(EntityID ID)
{
    uvs_[ID] = { -1,-1 };
}


void TextureComponentManager::SetUV(EntityID ID, const glm::vec2& uv)
{
    uvs_[ID] = uv;
}

glm::vec2& TextureComponentManager::GetUV(EntityID ID)
{
    return uvs_[ID];
}

bool TextureComponentManager::HasFilepath(EntityID ID)
{
  return filePaths_.find(ID) != filePaths_.end();
}

const std::string& TextureComponentManager::getFilePath(EntityID ID, unsigned int accessID)
{
    return filePaths_[ID][accessID];
}

void TextureComponentManager::SetFilePath(EntityID ID, const char *filePath, unsigned int accessID)
{
    filePaths_[ID][accessID] = std::string(filePath);
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

const std::vector<glm::uvec2>& TextureComponentManager::GetArrayDimensions()
{
    return dimensions_;
}

const std::vector<glm::vec2>& TextureComponentManager::GetArrayUVS()
{
    return uvs_;
}

const std::vector<glm::vec4>& TextureComponentManager::GetArrayColors()
{
    return colors_;
}

const std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>>& TextureComponentManager::GetArrayFilePath()
{
    return filePaths_;
}
