#include <UWUEngine/Component/TextureComp.h>
#include <array>
#include <UWUEngine/Modules/TextureAtlaserMod.h>

using namespace UWUEngine;

Texture TextureComp::operator[](EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], filePaths_[ID], atlas_layers[ID],atlas_uv[ID], atlas_scale[ID]);
}

UWUEngine::Texture TextureComp::getTexture(EntityID ID)
{
  return Texture(dimensions_[ID], uvs_[ID], colors_[ID], filePaths_[ID], atlas_layers[ID], atlas_uv[ID], atlas_scale[ID]);
}

void TextureComp::InitObject(EntityID ID)
{
  dimensions_[ID] = { 1, 1 };
  uvs_[ID] = { 0, 0 };
  colors_[ID] = { 1, 1, 1, 1 };
}

void TextureComp::SetAtlasData(EntityID ID, unsigned accessID)
{
  auto& texture = this->operator[](ID);
  auto filePath = texture.GetFilePaths(accessID);

  if (filePath == "")
  {
    return;
  }

  auto& TextureatlasMod = Get<TextureAtlaserMod>();

  auto& raw_data = TextureatlasMod.GetRawData(filePath);

  //auto it = filePath_to_RawData.find(filePath);
  //if (it == filePath_to_RawData.end())
  //{
  //  return;
  //}
  //auto& raw_data = it->second;

  auto width = raw_data.width;
  auto height = raw_data.height;
  auto u_scale = (TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.w*/ / static_cast<float>(width));
  auto v_scale = (TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.h*/ / static_cast<float>(height));
  auto Xoffset = raw_data.x_offset;
  auto Yoffset = raw_data.y_offset;

  auto u_coord = (static_cast<float>(Xoffset) / TA::MAX_SIZE_PAGE); //atlas_pages[vao_key].second.w;
  auto v_coord = (static_cast<float>(Yoffset) / TA::MAX_SIZE_PAGE); //atlas_pages[vao_key].second.h;

  atlas_uv[ID] = glm::vec2(u_coord, v_coord);
  atlas_scale[ID] = glm::vec2{ u_scale, v_scale };
  atlas_layers[ID] = raw_data.layer;
}

void UWUEngine::TextureComp::GetAtlasData(const char* filepath, glm::vec2* scale, glm::vec2* uvs, unsigned* layer)
{
  auto& TextureatlasMod = Get<TextureAtlaserMod>();

  auto& raw_data = TextureatlasMod.GetRawData(std::string(filepath));
  auto width = raw_data.width;
  auto height = raw_data.height;
  auto Xoffset = raw_data.x_offset;
  auto Yoffset = raw_data.y_offset;
  auto u_scale = TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.w*/ / static_cast<float>(width);
  auto v_scale = TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.h*/ / static_cast<float>(height);
  auto u_coord = static_cast<float>(Xoffset) / TA::MAX_SIZE_PAGE; //atlas_pages[vao_key].second.w;
  auto v_coord = static_cast<float>(Yoffset) / TA::MAX_SIZE_PAGE; //atlas_pages[vao_key].second.h;

  *scale = glm::vec2{ u_scale, v_scale };
  *uvs = glm::vec2{ u_coord, v_coord };
  *layer = raw_data.layer;
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
void Texture::SetAtlasLayer(const AtlasLayer& layer)
{
  atlas_layers_ = layer;
}

void Texture::SetAtlasUV(const glm::vec2& uv)
{
  atlas_uv_ = uv;
}

void UWUEngine::Texture::SetAtlasScale(const glm::vec2& scale)
{
  atlas_scale_ = scale;
}

void Texture::SetDimension(const glm::uvec2& dimension)
{
  dimensions_ = dimension;
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
const AtlasLayer& Texture::GetAtlasLayer() const
{
  return atlas_layers_;
}

const glm::vec2& Texture::GetAtlasUV() const
{
  return atlas_uv_;
}

const glm::vec2& Texture::GetAtlasScale() const
{
  return atlas_scale_;
}

const glm::uvec2& Texture::GetDimension() const
{
  return dimensions_;
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

void TextureComp::SetFilePath(EntityID ID, const char* filePath, unsigned accessID)
{
  Texture texture = getTexture(ID);
  texture.SetFilePath(std::string(filePath), accessID);
  SetAtlasData(ID);
}

void TextureComp::SetCurrentTexture(EntityID ID, unsigned accessID)
{
  SetAtlasData(ID, accessID);
}

void TextureComp::SetFilePaths(EntityID ID, const std::array<std::string, MAX_SPRITES>& filePaths)
{
  filePaths_[ID] = filePaths;
  SetAtlasData(ID);
}

#pragma region Array Getter
const EntityVector<AtlasLayer>& TextureComp::GetArrayAtlasLayers() const
{
  return atlas_layers;
}

const EntityVector<glm::vec2>& TextureComp::GetArrayAtlasUV() const
{
  return atlas_uv;
}

const EntityVector<glm::vec2>& UWUEngine::TextureComp::GetArrayAtlasScale() const
{
  return atlas_scale;
}

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

const std::unordered_map<EntityID, std::array<std::string, MAX_SPRITES>>& TextureComp::GetArrayFilePaths() const
{
  return filePaths_;
}
#pragma endregion 
