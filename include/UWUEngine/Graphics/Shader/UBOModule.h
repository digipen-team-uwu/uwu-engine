#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/constants.h>

namespace UWUEngine
{

class UBOModule : public System
{
public:
  UBOModule(ISpace*);
  ~UBOModule() = default;
  void Update() override {};

  enum Type
  {
    Camera,
    Light,
    HUDMatrices,
    Spine,

    Total
  };

  void CreateUBO(Type, unsigned size, unsigned location);

  unsigned GetUBOBindingLocation(Type);
  unsigned GetUBO_ID(Type);
  void ShootDataToUBO(Type, EntityID spineID = GameObjectConstants::INVALID_ID);
private:
  // uboId, location
  std::map<Type, std::pair<unsigned, unsigned>> data_;
};

}
