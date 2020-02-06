/******************************************************************************/
/*!
\par        Project Umbra
\file       AtlasModule.h
\author     Chau Nguyen
\date       2019/11/1
\brief      Atlasing textures

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <vector>
// include rectpack2D lib
#include <finders_interface.h>
#include <UWUEngine/Instances.h>
#include <UWUEngine/System.h>

using namespace rectpack2D;
namespace TA = TextureAtlasing;
using spaces_type = rectpack2D::empty_spaces<TA::allow_flip, default_empty_spaces>;
using rect_type = output_rect_t<spaces_type>;
using AtlasLayer = unsigned;
using Area = unsigned;

namespace UWUEngine
{

class AtlasModule : public System
{
private:
  class RawData; // forward declaration
public:
  AtlasModule(ISpace*);
  ~AtlasModule() = default;

  void ClearData();

  void LoadRawData(int total...);
  void LoadRawData(const std::vector<std::string>&);

  void CheckingLayer();
  void Atlasing(std::vector<RawData>& data_);
  void report_result(const rect_wh& result_size, const std::vector<rect_type>& rectangles);

  const std::vector<rect_type>& GetRectangles();
  const RawData& GetRawData(const std::string&);

  void LoadAtlasPage(GLboolean isTwice_ = false);

  const glm::vec2 GetAtlasUV(EntityID);
  const glm::vec2 GetAtlasScale(EntityID);

  const std::vector<glm::vec2>& GetArrayAtlasUV();
  const std::vector<glm::vec2>& GetArrayAtlasScale();

  //static void SetAtlasUVScale(EntityID id, unsigned int accessID = 0);

  void GetAtlasData(const char* filepath, glm::vec2* scale, glm::vec2* uvs, unsigned* layer);

  void SetAtlasLayers(EntityID, AtlasLayer);
  const AtlasLayer GetAtlasLayers(EntityID);
  const std::vector<AtlasLayer>& GetArrayAtlasLayer();

  const GLuint GetTextureID();

  glm::vec2 GetBrayanTexture(const std::string&);

  void SetAtlasData(EntityID id, unsigned int accessID = 0);

private:
  void Reset();

  class RawData
  {
  public:
    RawData() = default;
    ~RawData() = default;
    RawData(int x_offset_, int y_offset_, int width_, int height_, Area area_, int channels_,
            unsigned char* image_, const std::string& filePath_, VaoKey vao_key_, AtlasLayer atlas_layer_)
      : x_offset(x_offset_), y_offset(y_offset_), width(width_), height(height_), area(area_),
      channels(channels_), image(image_), filePath(filePath_), vao_key(vao_key_), layer(atlas_layer_)

    {};
    bool operator() (const RawData& r1, const RawData& r2);
    int x_offset;
    int y_offset;
    int width;
    int height;
    Area area;
    int channels;
    unsigned char* image;
    std::string filePath;
    VaoKey vao_key;
    AtlasLayer layer;
  };
  int max_side;
  int discard_step;
  flipping_option runtime_flipping_mode;
  GLuint texID;

  std::unordered_map<std::string, RawData> filePath_to_RawData;

  std::vector<rect_type> rectangles;

  EntityVector<AtlasLayer> atlas_layers;
  EntityVector<glm::vec2> atlas_uv;
  EntityVector<glm::vec2> atlas_scale;

  int layer_counter;
  int tracker_;
  int start_index_;
  bool is_first_pass_;

  std::vector<RawData> atlas_data_;
};

}