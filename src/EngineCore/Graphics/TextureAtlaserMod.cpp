#include <UWUEngine/Modules/TextureAtlaserMod.h>
#include "stb_image.h"
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Modules/TextureLoaderMod.h>
#include <cstdarg>
#include <UWUEngine/Component/TextureComp.h>
#include <UWUEngine/Systems/CompSpaceSys.h>

using namespace UWUEngine;

TextureAtlaserMod::TextureAtlaserMod(ISpace* space) : System(space)
{
  max_side = TA::MAX_SIZE_PAGE;
  discard_step = 1;
  // disable flipping image for best fit
  runtime_flipping_mode = flipping_option::DISABLED;
  stbi_set_unpremultiply_on_load(1);
  is_first_pass_ = true;
  layer_counter = 0;
}

void TextureAtlaserMod::ClearData()
{
  //free image ptrs
  for (auto it1 = filePath_to_RawData.begin(); it1 != filePath_to_RawData.end(); ++it1)
  {
    stbi_image_free(it1->second.image);
  }
  filePath_to_RawData.clear();
  atlas_data_.clear();
  Reset();
  glDeleteTextures(1, &texID);
  //TextureLoader::FlushCacheFiles();
}

void TextureAtlaserMod::Reset()
{
  is_first_pass_ = true;
  layer_counter = 0;
  start_index_ = 0;
  tracker_ = 0;
}

void TextureAtlaserMod::report_result(const rect_wh& result_size, const std::vector<rect_type>& rectangles)
{
  auto& logSys = Get<LogSys>();
  logSys.Log(logSys.DEBUG) << "Resultant atlas bin: " << result_size.w << " " << result_size.h << std::endl;

  for (const auto& r : rectangles) {
    logSys.Log(logSys.TRACE) << r.x << " " << r.y << " " << r.w << " " << r.h << std::endl;
  }
}

const std::vector<rect_type>& TextureAtlaserMod::GetRectangles()
{
  return rectangles;
}

const TextureAtlaserMod::RawData& TextureAtlaserMod::GetRawData(const std::string& filePath)
{
  return filePath_to_RawData.at(filePath);
}


void TextureAtlaserMod::CheckingLayer()
{
  if (is_first_pass_)
  {
    for (auto it = atlas_data_.begin(); it != atlas_data_.end(); ++it)
    {
      rectangles.emplace_back(rect_xywh(0, 0, it->width + TA::SIZE_OFFSET, it->height + TA::SIZE_OFFSET));
    }
    // update first pass check
    is_first_pass_ = false;
  }

  // create a root page
  auto packing_root = spaces_type({ max_side, max_side });
  packing_root.flipping_mode = runtime_flipping_mode;

  // init iterator
  auto r = rectangles.begin();

  while (!rectangles.empty())
  {
    for (; r != rectangles.end(); ++r)
    {
      if (const auto inserted_rectangle = packing_root.insert(std::as_const(*r).get_wh()))
      {
        *r = *inserted_rectangle;
      }
      else
      {
        // update start index
        start_index_ = tracker_;

        // increase layer counter
        ++layer_counter;

        // update container of rectangles
        rectangles.assign(r, rectangles.end());

        // update layer_counter
        for (int j = 0; j < rectangles.size(); ++j)
        {
          filePath_to_RawData.find(atlas_data_[j + start_index_].filePath)->second.layer = layer_counter;
        }
        // update iterator
        r = rectangles.begin();
        // create new root page
        packing_root = spaces_type({ max_side, max_side });
        packing_root.flipping_mode = runtime_flipping_mode;
      }
      // update tracker
      ++tracker_;
    }
    // clear after done using
    rectangles.clear();
  }
}

void TextureAtlaserMod::Atlasing(std::vector<RawData>& data_)
{
  auto report_successful = [](rect_type&) {
    return callback_result::CONTINUE_PACKING;
  };

  auto report_unsuccessful = [](rect_type&) {
    return callback_result::ABORT_PACKING;
  };

  for (auto it = data_.begin(); it != data_.end(); ++it)
  {
    rectangles.emplace_back(rect_xywh(0, 0, it->width + TA::SIZE_OFFSET, it->height + TA::SIZE_OFFSET));
  }
  //Find best packing using all provided custom rectangle orders.
  using rect_ptr = rect_type*;

  auto my_custom_order_1 = [](const rect_ptr a, const rect_ptr b) {
    return a->get_wh().pathological_mult() > b->get_wh().pathological_mult();
  };

  auto my_custom_order_2 = [](const rect_ptr a, const rect_ptr b) {
    return a->get_wh().pathological_mult() < b->get_wh().pathological_mult();
  };

  auto atlas_page = find_best_packing<spaces_type>(
    rectangles,
    make_finder_input(
      max_side,
      discard_step,
      report_successful,
      report_unsuccessful,
      runtime_flipping_mode
    ),
    my_custom_order_1,
    my_custom_order_2
    );
#ifdef _DEBUG
  report_result(atlas_page, rectangles);
#endif
  // update uv offset
  for (int i = 0; i < rectangles.size(); ++i)
  {
    filePath_to_RawData.find(data_[i].filePath)->second.x_offset = rectangles[i].x;
    filePath_to_RawData.find(data_[i].filePath)->second.y_offset = rectangles[i].y;
  }
  rectangles.clear();
}

bool TextureAtlaserMod::RawData::operator()(const RawData& r1, const RawData& r2)
{
  return r1.area < r2.area;
}

void TextureAtlaserMod::LoadAtlasPage(GLboolean isTwice_)
{
  if (isTwice_)
  {
    ClearData();
  }
  auto& textureLoader = Get<TextureLoaderMod>();
  textureLoader.LoadCacheFiles();
  LoadRawData(textureLoader.GetLoadCache());

  for (auto& i : filePath_to_RawData)
  {
    atlas_data_.push_back(i.second);
  }

  std::sort(atlas_data_.begin(), atlas_data_.end(), RawData());

  CheckingLayer();

  std::map<AtlasLayer, std::vector<RawData>> atlasdata;
  for (auto& i : filePath_to_RawData)
  {
    atlasdata[i.second.layer].push_back(i.second);
  }

  for (auto it = atlasdata.begin(); it != atlasdata.end(); ++it)
  {
    auto& raw_data = it->second;
    std::sort(raw_data.begin(), raw_data.end(), RawData());
  }

  for (auto& j : atlasdata)
  {
    Atlasing(j.second);
  }

  glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &texID);

  glTextureParameteri(texID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(texID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(texID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texID, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTextureParameteri(texID, GL_TEXTURE_WRAP_R, GL_REPEAT);

  // allocate GPU texture buffer storage for atlas page
  //glTextureStorage2D(textureID, 1, GL_RGBA8, atlas_page.w, atlas_page.h);
  glTextureStorage3D(texID, TA::MIPMAP_LEVEL, GL_RGBA8,
    TA::MAX_SIZE_PAGE,
    TA::MAX_SIZE_PAGE,
    TA::MAX_LAYERS);

  // copy data from CPU to texture buffer
  for (auto it1 = filePath_to_RawData.begin(); it1 != filePath_to_RawData.end(); ++it1)
  {
    glTextureSubImage3D(texID, 0, it1->second.x_offset + TA::OFFSET_OFFSET, it1->second.y_offset + TA::OFFSET_OFFSET, it1->second.layer,
      it1->second.width, it1->second.height, 1, GL_RGBA, GL_UNSIGNED_BYTE, it1->second.image);
    glGenerateTextureMipmap(texID);
  }

  // bind to texture unit 0
  glBindTextureUnit(0, texID);

  // create instance vbos and get correspond vao key
  //VaoKey vao_key = Instances::CreateInstances(Mesh::GetEntityMesh());

  // set entity vao key
  //Instances::SetEntityVAOKey(vao_key);

  // setting atlas uv and atlas scale for all spaces
  auto& compSys = Get<CompSpaceSys>();

  auto& entity_environment = compSys.space_environment.Get<EntityComp>().GetIDs();
  auto& entity_ui = compSys.space_ui.Get<EntityComp>().GetIDs();
  auto& entity_debug = compSys.space_ui.Get<EntityComp>().GetIDs();

  auto& tex_environment = compSys.space_environment.Get<TextureComp>();
  auto& tex_ui = compSys.space_ui.Get<TextureComp>();
  auto& tex_debug = compSys.space_ui.Get<TextureComp>();

  for (int i = 0; i < entity_environment.size(); ++i)
  {
    tex_environment.SetAtlasData(i);
  }

  for (int i = 0; i < entity_ui.size(); ++i)
  {
    tex_ui.SetAtlasData(i);
  }
  
  for (int i = 0; i < entity_debug.size(); ++i)
  {
    tex_debug.SetAtlasData(i);
  }
}

void TextureAtlaserMod::LoadRawData(const std::vector<std::string>& files)
{
  for (auto it = files.begin(); it != files.end(); ++it)
  {
    int image_width;
    int image_height;
    int number_channels;
    unsigned char* image;

    image = stbi_load(it->c_str(), &image_width, &image_height, &number_channels, 0);

    if (image)
    {
      Area area = image_width * image_height;
      RawData raw = RawData(0, 0, image_width, image_height, area, number_channels, image,
        *it, layer_counter);
      filePath_to_RawData.insert({ *it, raw });
    }
    else
    {
      Get<LogSys>().Log(Get<LogSys>().FAILURE) << "Failed to load texture" << std::endl;
      std::exit(-1);
    }
  }
}

void TextureAtlaserMod::LoadRawData(int total...)
{
  va_list args;
  va_start(args, total);

  for (int i = 0; i < total; ++i)
  {
    const char* filePath = va_arg(args, const char*);

    int image_width;
    int image_height;
    int number_channels;
    unsigned char* image;

    image = stbi_load(filePath, &image_width, &image_height, &number_channels, 0);

    if (image)
    {
      Area area = image_width * image_height;
      RawData raw = RawData(0, 0, image_width, image_height, area, number_channels, image,
        filePath, layer_counter);
      filePath_to_RawData.find(filePath)->second = raw;
    }
    else
    {
      Get<LogSys>().Log(Get<LogSys>().FAILURE) << "Failed to load texture" << std::endl;
      exit(-1);
    }
  }
  va_end(args);
}

const GLuint TextureAtlaserMod::GetTextureID()
{
  return texID;
}
