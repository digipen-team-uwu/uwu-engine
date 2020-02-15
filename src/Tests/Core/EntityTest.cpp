#include <catch2/catch.hpp>
#include <UWUEngine/Systems/AllSystems.h>
#include <UWUTest/Engine.hpp>

using namespace UWUEngine;

TEST_CASE("Entity Creation and Deletion")
{
  SECTION("Vector test = 1 Object")
  {
    auto *engine = new UWUTest::Engine<LogSys, EntitySys, CompSpaceSys>;
    auto &sys = engine->GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    
    sys.Get<EntitySys>().CreateEntity(&game);

    REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1);
    delete engine;
  }
  SECTION("Vector test - 1000000 Objects")
  {
    class A{};
    auto *engine = new UWUTest::Engine<LogSys, EntitySys, CompSpaceSys>;
    auto &sys = engine->GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;

    for(int i = 0; i < 4000; ++i)
    {
      sys.Get<EntitySys>().CreateEntity(&game);
    }

    REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1 << 12);
    delete engine;
  }
  SECTION("Entity Deletion test - 100 Objects, delete 20")
  {
    auto* engine = new UWUTest::Engine<LogSys, EntitySys, CompSpaceSys>;
    auto &sys = engine->GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    std::vector<EntityID> vec;
    for(int i = 0; i < 100; ++i)
    {
      vec.push_back(sys.Get<EntitySys>().CreateEntity(&game));
    }

    for(int i = 0; i < 100; i += 5)
    {
      sys.Get<EntitySys>().DestroyEntity(&game, vec[i]);
    }

    engine->Step();
    auto &ids = game.Get<EntityComp>().GetIDs();
    REQUIRE(ids.size() == 80);

    delete engine;
  }
}
