#include <vector>
#include <rttr/type.h>
#include <UWUEngine/BaseSystem.h>

namespace UWUEngine
{
using EntityID = unsigned int;
class Reflection : public BaseSystem<Reflection>
{
public:
  Reflection();
  void ReflectObject(EntityID id);
  std::vector<rttr::instance>& getInstances(EntityID id);
private:
  std::vector<std::vector<rttr::instance>> data;
};
}