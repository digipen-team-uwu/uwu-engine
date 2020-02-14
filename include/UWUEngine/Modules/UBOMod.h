#pragma once
#include <UWUEngine/System.h>
#include <map>
#include <UWUEngine/constants.h>

using EntityID = unsigned;

namespace UWUEngine
{
  class UBOMod : public System
  {
  public:
    UBOMod(ISpace* space);
    ~UBOMod() override = default;
    
    enum Type
    {
      Camera,
      Light,
      HUDMatrices,
      Spine,

      Total
    };

    void CreateUniformBuffer(UBOMod::Type, unsigned size, unsigned location);

    unsigned GetUniformBufferBindingLocation(UBOMod::Type);
    unsigned GetUniformBufferID(UBOMod::Type);
    void ShootDataToUniformBuffer(UBOMod::Type, EntityID spineID = GameObjectConstants::INVALID_ID);
  private:
    // uboId, location
    std::map<UBOMod::Type, std::pair<unsigned, unsigned>> data_;
  };
}