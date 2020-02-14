#include <catch2/catch.hpp>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Space.h>

using namespace UWUEngine;

TEST_CASE("Creating Object")
{
  SECTION("Vector test = 1 Object")
  {
    Engine engine{};
    auto &sys = engine.GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    
    sys.Get<EntitySys>().CreateEntity(&game);

    REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1);
  }
  SECTION("Vector test - 1000000 Objects")
  {
    Engine engine{};
    auto &sys = engine.GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;

    for(int i = 0; i < 1000000; ++i)
    {
      sys.Get<EntitySys>().CreateEntity(&game);
    }

    REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1 << 20);
  }
  SECTION("Entity Deletion test - 100 Objects, delete 20")
  {
    Engine engine{};
    auto &sys = engine.GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    std::stack<EntityID> stack;
    for(int i = 0; i < 100; ++i)
    {
      stack.push(sys.Get<EntitySys>().CreateEntity(&game));
    }

    for(int i = 0; i < 100; i += 5)
    {
      sys.Get<EntitySys>().DestroyEntity(&game, stack.top());
      stack.pop();
    }
    auto &ids = game.Get<EntityComp>().GetIDs();
    //REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1);
  }
}