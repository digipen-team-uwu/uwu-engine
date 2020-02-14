#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/constants.h>

using EntityID = unsigned;

namespace UWUEngine
{
  class SSBOMod : public System
  {
  public:
    SSBOMod(ISpace* space);
    ~SSBOMod() = default;
    enum Type
    {
      PointLight,
      DirectionalLight,
      SpotLight,

      Total
    };

    void CreateShaderStorageBufferObject(Type, unsigned size, unsigned location);

    unsigned GetShaderStorageBufferObjectBindingLocation(Type);
    unsigned GetShaderStorageBufferObjectSize(Type);
    unsigned GetShaderStorageBufferObjectID(Type);
    void ShootDataToShaderStorageBufferObject(Type);
  private:
    // ssboId, location, size
    std::map<Type, std::tuple<unsigned, unsigned, unsigned>> data_;
    // TODO: vector of point light, directional light, spot light
  };
}