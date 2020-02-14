#include <catch2/catch.hpp>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Space.h>

using namespace UWUEngine;

TEST_CASE("Entity Creation and Deletion")
{
  SECTION("Vector test = 1 Object")
  {
    auto *engine = new Engine;
    auto &sys = engine->GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    
    sys.Get<EntitySys>().CreateEntity(&game);

    REQUIRE(game.Get<EntityComp>().GetVectorSize() == 1);
    delete engine;
  }
  SECTION("Vector test - 1000000 Objects")
  {
    auto *engine = new Engine;
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
    Engine engine{};
    auto &sys = engine.GetSystems();
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
    engine.Step();
    auto &ids = game.Get<EntityComp>().GetIDs();
    REQUIRE(ids.size() == 80);
  }
}

TEST_CASE("Physics")
{
  SECTION("Acceleration test - multiple component spaces")
  {
    Engine engine{};
    auto &sys = engine.GetSystems();
    auto &game = sys.Get<CompSpaceSys>().space_gameplay;
    auto &part = sys.Get<CompSpaceSys>().space_particle;
    EntityID obj1 = sys.Get<EntitySys>().CreateEntity(&game);
    EntityID obj2 = sys.Get<EntitySys>().CreateEntity(&part);
    Physics phy1 = game.Get<PhysicsComp>().getPhysics(obj1);
    Physics phy2 = part.Get<PhysicsComp>().getPhysics(obj2);
    phy1.SetAcceleration({100, 0, 0, 0});
    phy1.SetInverseMass(1);
    phy2.SetAcceleration({-100, 0, 0, 0});
    phy2.SetInverseMass(1);
    engine.Step();
    engine.Step();
    REQUIRE(phy1.GetVelocity().x > 0);
    REQUIRE(phy2.GetVelocity().x < 0);
  }
}