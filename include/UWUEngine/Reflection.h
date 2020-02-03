#include <vector>
#include <ponder/classbuilder.hpp> //DO THIS ORDER.... or else... ill f*********** kill you
#include<ponder/uses/runtime.hpp>

using EntityID = unsigned int;
class Reflection
{
  void ReflectObject(EntityID id);
private:
  std::vector<std::vector<ponder::UserObject>> data;
};