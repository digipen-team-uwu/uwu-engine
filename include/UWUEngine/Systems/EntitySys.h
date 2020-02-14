#include <UWUEngine/System.h>
using EntityID = unsigned int;
namespace UWUEngine
{
class EntitySys : public System
{
public:
  EntitySys(ISpace *s) : System(s){}
  ~EntitySys() = default;
  void Update() override;
  EntityID CreateEntity(ISpace*);
  void DestroyEntity(ISpace*, EntityID id);
};
}