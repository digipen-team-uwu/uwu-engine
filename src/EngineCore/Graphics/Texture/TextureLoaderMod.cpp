#include <UWUEngine/Modules/TextureLoaderMod.h>

using namespace UWUEngine;

TextureLoaderMod::TextureLoaderMod(ISpace* p):
System(p)
{
  InitCache();
}

TextureLoaderMod::~TextureLoaderMod()
{
  ResetCache();
}

void TextureLoaderMod::Update()
{
}

void TextureLoaderMod::LoadCacheFiles()
{
  //TODO:HADI
  //auto& filePath = TextureComponentManager::GetArrayFilePath();

  //for (auto it = filePath.begin(); it != filePath.end(); ++it)
  //{
  //  for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
  //  {
  //    CheckIfLoadDifferFilePath(*jt);

  //    if (!cache_ && !jt->empty())
  //    {
  //      cache_file.push_back(*jt);
  //      TurnCacheOn();
  //    }
  //  }
  //}

  //auto& filePath2 = EntityCacher::GetCachedFilepaths();
  //for (auto it = filePath2.begin(); it != filePath2.end(); ++it)
  //{
  //  CheckIfLoadDifferFilePath(*it);

  //  if (!cache_ && !it->empty())
  //  {
  //    cache_file.push_back(*it);
  //    TurnCacheOn();
  //  }
  //}
}

const std::vector<std::string>& TextureLoaderMod::GetLoadCache()
{
  return cache_file;
}

void TextureLoaderMod::FlushCacheFiles()
{
  cache_file.clear();
}

void TextureLoaderMod::InitCache()
{
  cache_ = false;
}

void TextureLoaderMod::CheckIfLoadDifferFilePath(const std::string& filePath)
{
  for (auto it = cache_file.begin(); it != cache_file.end(); ++it)
  {
    if (*it == filePath || filePath == "")
    {
      return;
    }
  }
  TurnCacheOff();
}

void TextureLoaderMod::TurnCacheOn()
{
  cache_ = true;
}

void TextureLoaderMod::TurnCacheOff()
{
  cache_ = false;
}

void TextureLoaderMod::ResetCache()
{
  TurnCacheOff();
}

 