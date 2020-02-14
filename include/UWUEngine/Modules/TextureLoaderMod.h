
#pragma once

#include <UWUEngine/System.h>

#include <vector>
#include <string>

namespace UWUEngine
{
  class TextureLoaderMod : public System
  {
  public:
    TextureLoaderMod(ISpace* p);
    ~TextureLoaderMod() override;
    void Update() override;

    void LoadCacheFiles();

    const std::vector<std::string>& GetLoadCache();
    void FlushCacheFiles();

  private:
    // cache system
    void InitCache();
    void CheckIfLoadDifferFilePath(const std::string&);
    void TurnCacheOn();
    void TurnCacheOff();
    void ResetCache();
    bool cache_;
    std::vector<std::string> cache_file;
  };
}
