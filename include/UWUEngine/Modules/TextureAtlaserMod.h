#pragma once
#include <UWUEngine/System.h>
#include <glm/gtx/transform.hpp>
#include <unordered_map>
#include <UWUEngine/constants.h>
// include rectpack2D lib
#include "finders_interface.h"
#include <UWUEngine/Component/EntityComp.h>

using namespace rectpack2D;
namespace TA = TextureAtlasing;
using spaces_type = rectpack2D::empty_spaces<TA::allow_flip, default_empty_spaces>;
using rect_type = output_rect_t<spaces_type>;
using AtlasLayer = unsigned;
using Area = unsigned;

namespace UWUEngine
{
  class TextureAtlaserMod : public System
  {
    class RawData; // forward declaration
  public:
    TextureAtlaserMod(ISpace* space);
    ~TextureAtlaserMod();

    void ClearData();

    void LoadRawData(int total...);
    void LoadRawData(const std::vector<std::string>&);

    void CheckingLayer();
    void Atlasing(std::vector<RawData> & data_);
    void report_result(const rect_wh & result_size, const std::vector<rect_type> & rectangles);

    const std::vector<rect_type>& GetRectangles();
    const RawData& GetRawData(const std::string&);

    void LoadAtlasPage(GLboolean isTwice_ = false);

    const GLuint GetTextureID();

  private:
    void Reset();

    class RawData
    {
    public:
      RawData() = default;
      ~RawData() = default;
      RawData(int x_offset_, int y_offset_, int width_, int height_, Area area_, int channels_,
        unsigned char* image_, const std::string& filePath_, AtlasLayer atlas_layer_)
        : x_offset(x_offset_), y_offset(y_offset_), width(width_), height(height_), area(area_),
        channels(channels_), image(image_), filePath(filePath_), layer(atlas_layer_)

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
      AtlasLayer layer;
    };
    int max_side;
    int discard_step;
    flipping_option runtime_flipping_mode;
    GLuint texID;

    std::unordered_map<std::string, RawData> filePath_to_RawData;

    std::vector<rect_type> rectangles;

    int layer_counter;
    int tracker_;
    int start_index_;
    bool is_first_pass_;

    std::vector<RawData> atlas_data_;
  };
}