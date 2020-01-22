/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureLoader.cpp
\author     Chau Nguyen
\date       2019/10/29
\brief      Loading file paths into cache

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityCacher.h>
#include <UWUEngine/Graphics/Texture/TextureLoader.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Component/TextureComponentManager.h>



std::vector<std::string> TextureLoader::cache_file;
bool TextureLoader::cache_;

TextureLoader::TextureLoader()
{
    InitCache();
}

TextureLoader::~TextureLoader()
{
    ResetCache();
}

void TextureLoader::LoadCacheFiles()
{
    auto& filePath = TextureComponentManager::GetArrayFilePath();

    for (auto it = filePath.begin(); it != filePath.end(); ++it)
    {
      for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
      {
        CheckIfLoadDifferFilePath(*jt);

        if (!cache_ && !jt->empty())
        {
          cache_file.push_back(*jt);
          TurnCacheOn();
        }
      }
    }

   auto& filePath2 = EntityCacher::GetCachedFilepaths();
   for (auto it = filePath2.begin(); it != filePath2.end(); ++it)
   {
       CheckIfLoadDifferFilePath(*it);

       if (!cache_ && !it->empty())
       {
         cache_file.push_back(*it);
         TurnCacheOn();
       }
   }
}

const std::vector<std::string>& TextureLoader::GetLoadCache()
{
    return cache_file;
}

void TextureLoader::FlushCacheFiles()
{
    cache_file.clear();
}

void TextureLoader::InitCache()
{
    cache_ = false;
}

void TextureLoader::CheckIfLoadDifferFilePath(const std::string& filePath)
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

void TextureLoader::TurnCacheOn()
{
    cache_ = true;
}

void TextureLoader::TurnCacheOff()
{
    cache_ = false;
}

void TextureLoader::ResetCache()
{
    TurnCacheOff();
}
