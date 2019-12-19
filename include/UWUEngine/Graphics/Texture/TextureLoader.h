/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureLoader.h
\author     Chau Nguyen
\date       2019/10/29
\brief      Loading file paths into cache

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/BaseSystem.h>
#include <string>

class TextureLoader : public BaseSystem<TextureLoader>
{
public:
    TextureLoader();
    ~TextureLoader();
    void Update() override {};

    static void LoadCacheFiles();

    static const std::vector<std::string>& GetLoadCache();
    static void FlushCacheFiles();

private:
    // cache system
    static void InitCache();
    static void CheckIfLoadDifferFilePath(const std::string&);
    static void TurnCacheOn();
    static void TurnCacheOff();
    static void ResetCache();
    static bool cache_;
    static std::vector<std::string> cache_file;
};
