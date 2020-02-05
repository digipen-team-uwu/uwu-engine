#include <vector>
#include <rttr/type.h>

using EntityID = unsigned int;
class Reflection
{
  void ReflectObject(EntityID id);
private:
  std::vector<std::vector<rttr::type>> data;
};