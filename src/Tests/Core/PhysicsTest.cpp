#include <catch2/catch.hpp>
#include <UWUEngine/Systems/AllSystems.h>
#include <UWUTest/Engine.hpp>

using namespace UWUEngine;

#include <UWUTest/Systems/HeadlessWindowSys.hpp>
#include <UWUTest/Systems/LockedFrameLimiterSys.hpp>

TEST_CASE("Physics")
{
  SECTION("Velocity test - single component space")
  {
    auto* engine = new UWUTest::Engine<LogSys, UWUTest::HeadlessWindowSys, UWUTest::LockedFrameLimiterSys<60>, PhysicsSys, EntitySys, CompSpaceSys>;
    auto& sys = engine->GetSystems();

    auto& game = sys.Get<CompSpaceSys>().space_gameplay;

    EntityID obj1 = sys.Get<EntitySys>().CreateEntity(&game);

    Physics phy1 = game.Get<PhysicsComp>().getPhysics(obj1);

    phy1.SetVelocity({ 100, 0, 0, 0 });
    phy1.SetInverseMass(1);

    engine->Step();
    engine->Step();

    Transform trans1 = game.Get<TransformComp>().getTransform(obj1);

    REQUIRE(trans1.GetTranslation().x > 0.f);

    delete engine;
  }

  SECTION("Acceleration test - multiple component spaces")
  {
    auto* engine = new UWUTest::Engine<LogSys, UWUTest::HeadlessWindowSys, UWUTest::LockedFrameLimiterSys<60>, PhysicsSys, EntitySys, CompSpaceSys>;
    auto& sys = engine->GetSystems();

    auto& game = sys.Get<CompSpaceSys>().space_gameplay;
    auto& part = sys.Get<CompSpaceSys>().space_particle;

    EntityID obj1 = sys.Get<EntitySys>().CreateEntity(&game);
    EntityID obj2 = sys.Get<EntitySys>().CreateEntity(&part);

    Physics phy1 = game.Get<PhysicsComp>().getPhysics(obj1);
    Physics phy2 = part.Get<PhysicsComp>().getPhysics(obj2);

    phy1.SetAcceleration({ 100, 0, 0, 0 });
    phy1.SetInverseMass(1);
    phy2.SetAcceleration({ -100, 0, 0, 0 });
    phy2.SetInverseMass(1);

    engine->Step();
    engine->Step();

    REQUIRE(phy1.GetVelocity().x > 0.f);
    REQUIRE(phy2.GetVelocity().x < 0.f);

    delete engine;
  }
}