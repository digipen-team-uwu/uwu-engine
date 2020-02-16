#include <catch2/catch.hpp>
#include <iostream>

#include <UWUTest/Engine.hpp>
#include <UWUTest/Systems/HeadlessWindowSys.hpp>

#include <UWUEngine/Systems/EventSys.h>
#include <UWUEngine/Systems/LogSys.h>

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
      UNSCOPED_INFO("Callable listener"<< ID <<" receives event");
      UNSCOPED_INFO("Event content: " << event.content);
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

    void MemberListener(const Event<EventType::Test>& event) const
    {
      UNSCOPED_INFO("Member function listener" << ID << " receives event");
      UNSCOPED_INFO("Event content: " << event.content);
      Member1 = true;
    }

    int ID;
    EventListener<EventType::Test> listener{MemberFunc(&CallAbleListener::MemberListener)};
  };

  void FunctionListener(const Event<EventType::Test>& event)
  {
    UNSCOPED_INFO("Function listener receives event");
    UNSCOPED_INFO("Event content: " << event.content);
    Function1 = true;
  }
}

TEST_CASE("Event System")
{
  auto* engine = new UWUTest::Engine<
  LogSys,
  EventSys,
  UWUTest::HeadlessWindowSys>;

  auto& eventSys = engine->GetSystems().Get<EventSys>();

  SECTION("Listener registration")
  {
    const EventListener<EventType::Test> listener1{ FunctionListener };
    const EventListener<EventType::Test> listener2{ FunctionListener };
    const EventListener<EventType::Test> listener3{ FunctionListener };
    const EventListener<EventType::Test> listener4{ FunctionListener };

    INFO("Register listeners");
    eventSys.Register(listener1);
    eventSys.Register(listener2);
    eventSys.Register(listener3);
    eventSys.Register(listener4);

    auto& dispatcher = eventSys.GetDispatcher<EventType::Test>();
    REQUIRE(dispatcher.ListenerCount() == 4);

    INFO("UnRegister listeners")
    eventSys.UnRegister(listener1);
    eventSys.UnRegister(listener2);
    eventSys.UnRegister(listener3);
    eventSys.UnRegister(listener4);
    REQUIRE(dispatcher.ListenerCount() == 0);
  }

  SECTION("Push a test event")
  {
    const EventListener<EventType::Test> listener1{ FunctionListener };

    INFO("Register listeners");
    eventSys.Register(listener1);

    INFO("Push a test event");
    eventSys.Push(Event<EventType::Test>("This is function listener test"));

    auto& dispatcher = eventSys.GetDispatcher<EventType::Test>();
    REQUIRE(dispatcher.EventCount() == 1);

    INFO("Dispatch events");
    engine->Step();

    REQUIRE(Function1);
    eventSys.UnRegister(listener1);
  }

  SECTION("Callable Object")
  {
    const CallAbleListener obj1{ 0 };
    const CallAbleListener obj2{ 1 };

    const EventListener<EventType::Test> listener1{ obj1 };
    const EventListener<EventType::Test> listener2{ obj2 };

    eventSys.Register(listener1);
    eventSys.Register(listener2);

    eventSys.Push(Event<EventType::Test>("This is a callable object test"));
    engine->Step();

    REQUIRE(Callable1);
    REQUIRE(Callable2);

    eventSys.UnRegister(listener1);
    eventSys.UnRegister(listener2);
  }

  SECTION("Member Function")
  {
    const CallAbleListener obj1{ 0 };
    const CallAbleListener obj2{ 1 };

    eventSys.Register(obj1.listener);
    eventSys.Register(obj2.listener);

    eventSys.Push(Event<EventType::Test>("This is a member function test"));
    engine->Step();

    REQUIRE(Member1);

    eventSys.UnRegister(obj1.listener);
    eventSys.UnRegister(obj2.listener);
  }

  delete engine;
}