#include <vector>
#include <rttr/type.h>
#include <UWUEngine/System.h>

namespace UWUEngine
{
using EntityID = unsigned int;

class ReflectionModule : public System
{
public:
  ReflectionModule();
  template<class SpaceType>
  void ReflectObject(SpaceType& space, EntityID id)
  {
    //for ( auto it : iterate over components )
    for (auto it : space)
      it.second.GetInstance();
    rttr::instance eve(event);
    data[id].push_back(eve);
    //std::string str = io::to_json(eve);
  }
  std::vector<rttr::instance>& getInstances(EntityID id);
private:
  std::vector<std::vector<rttr::instance>> data;
};
}