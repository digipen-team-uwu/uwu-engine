#include <catch2/catch.hpp>
#include <iostream>

#include <UWUTest/Engine.hpp>
#include <UWUTest/Systems/HeadlessWindowSys.hpp>

#include <UWUEngine/Systems/EventSys.h>

using namespace UWUEngine;

namespace
{
  bool Callable1{ false };
  bool Callable2{ false };

  bool Function1{ false };

  bool Member1{ false };

  const std::string testString = "This is a test string";

  struct CallAbleListener
  {
    CallAbleListener(int ID):ID(ID){}
    void operator()(const Event<EventType::Test>& event)
    {
      switch (ID)
      {
        case 0:
          Callable1 = true;
          break;

        case 1:
          Callable2 = true;
          break;

        default:
          break;
      }
    }

    void MemberListener(const Event<EventType::Test>& event)
    {
      Member1 = true;
    }

    int ID;
    EventListener<EventType::Test> listener{MemberFunc(&CallAbleListener::MemberListener)};
  };

  void FunctionListener(const Event<EventType::Test>& event)
  {
    Function1 = true;
  }
}

TEST_CASE("Event System")
{
  auto* engine = new UWUTest::Engine<EventSys, UWUTest::HeadlessWindowSys>;
  auto& eventSys = engine->GetSystems().Get<EventSys>();

  SECTION("Push a test event")
  {
    const EventListener<EventType::Test> listener1{ FunctionListener };

    eventSys.Register(listener1);

    eventSys.Push(Event<EventType::Test>("This is test event 1"));
    engine->Step();

    REQUIRE(Function1);
  }

  SECTION("Callable Object")
  {
    const CallAbleListener obj1{ 0 };
    const CallAbleListener obj2{ 1 };

    const EventListener<EventType::Test> listener1{ obj1 };
    const EventListener<EventType::Test> listener2{ obj2 };

    eventSys.Register(listener1);
    eventSys.Register(listener2);

    eventSys.Push(Event<EventType::Test>("This is test event 2"));
    engine->Step();

    REQUIRE(Callable1);
    REQUIRE(Callable2);
  }

  SECTION("Member Function")
  {
    const CallAbleListener obj1{ 0 };
    const CallAbleListener obj2{ 1 };

    eventSys.Register(obj1.listener);
    eventSys.Register(obj2.listener);

    eventSys.Push(Event<EventType::Test>("This is test event 3"));
    engine->Step();

    REQUIRE(Member1);
  }

  delete engine;
}