#include <iostream>
#include <string>

#include <ponder/classbuilder.hpp> //DO THIS ORDER.... or else... ill f*********** kill you
#include <ponder/uses/runtime.hpp>


class dog
{
public:
  dog(std::string name):name(name){}
  void Say()
  {
    std::cout << "I'm " << name << std::endl;
  }

private:
  std::string name;
};

PONDER_TYPE(dog)

int main(int argc, char* argv[])
{
  ponder::Class::declare<dog>("dog")
  .constructor<std::string>()
  .function("Say", &dog::Say);

  const ponder::Class& dogClass = ponder::classByName("dog");
  ponder::UserObject dog1 = ponder::runtime::create(dogClass, "Stupid");

  const ponder::Function& dogSay = dogClass.function("Say");

  ponder::runtime::ObjectCaller(dogSay).call(dog1);

  std::cout << "Test" <<std::endl;

  return 0;
}

