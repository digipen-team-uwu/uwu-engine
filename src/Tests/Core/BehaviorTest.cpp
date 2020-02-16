#include <catch2/catch.hpp>
#include <UWUEngine/Systems/AllSystems.h>
#include <UWUTest/Engine.hpp>

using namespace UWUEngine;

#include <UWUTest/Systems/HeadlessWindowSys.hpp>
#include <UWUTest/Systems/LockedFrameLimiterSys.hpp>

TEST_CASE("Behavior")
{
  SECTION("Fall tag test")
  {
    auto* engine = new UWUTest::Engine<LogSys, UWUTest::HeadlessWindowSys, UWUTest::LockedFrameLimiterSys<60>, PhysicsSys, EntitySys, CompSpaceSys, BehaviorSys>;
    auto& sys = engine->GetSystems();

    auto& game = sys.Get<CompSpaceSys>().space_particle;

    EntityID obj1 = sys.Get<EntitySys>().CreateEntity(&game);

    game.Get<EntityComp>().AddTag(obj1, EntityComp::Tag::FALLS);

    engine->Step();
    engine->Step();

    Physics phy1 = game.Get<PhysicsComp>().getPhysics(obj1);

    REQUIRE(phy1.GetAcceleration().y < 0.f);

    delete engine;
  }
}