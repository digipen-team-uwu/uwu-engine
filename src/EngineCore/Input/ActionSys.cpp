#include <UWUEngine/Input/ActionSys.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Helper.h>


#ifdef REGISTERED
#undef REGISTERED
#endif

#ifdef UNREGISTERED
#undef UNREGISTERED
#endif

namespace ic = InputConstants;

namespace UWUEngine
{

ActionSys::ActionSys(ISpace* p) : System(p), actions{}, prevActions{}
{}


ic::InputResult ActionSys::GetAction(Action action) const
{
  return ic::InputResult(actions[action]);
}

bool ActionSys::GetAction(Action action, const std::vector<ic::InputResult>& results) const
{
  bool returnVal = false;

  for (auto result : results)
  {
    if (actions[action] == result)
    {
      returnVal = true;
    }
  }
  return returnVal;
}

bool ActionSys::GetActionPressed(Action action) const
{
  return actions[action] == ic::PRESSED;
}

bool ActionSys::GetActionHeld(Action action) const
{
  return actions[action] == ic::HELD;
}

bool ActionSys::GetActionReleased(Action action) const
{
  return actions[action] == ic::RELEASED;
}

bool ActionSys::GetInaction(Action action) const
{

  return actions[action] == ic::NONE;
}

glm::vec2 ActionSys::GetDashVec(int controllerID) const
{
  if (InputManager::KeyPressed(' ')) //TODO: Player to Mouse vector
    return glm::vec2(.5f, .75f);
  return InputManager::GetJoyAxis(InputConstants::RIGHTJ);
}

float ActionSys::GetDashAngle(int controllerID) const
{
  if (InputManager::KeyPressed(' '))//TODO: Player to Mouse vector angle
    return glm::radians(75.0f);
  return InputManager::GetJoyRads(InputConstants::RIGHTJ);//glm::angle(InputManager::GetJoyAxis(InputConstants::RIGHTJ), glm::vec2(1.f,0.f));
}

void ActionSys::Update()
{ 
  std::swap(actions, prevActions);
  std::fill(actions.begin(), actions.end(), ic::UNREGISTERED);

  if (InputManager::ButtonPressed(ic::A))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Select \n");

    actions[Select] = ic::REGISTERED;
  }

  if (InputManager::ButtonPressed(ic::BACK) || InputManager::KeyPressed('b')
      || InputManager::ButtonPressed(ic::B))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Back \n");

    actions[Back] = ic::REGISTERED;
  }
  if (InputManager::ButtonPressed(ic::START) || InputManager::KeyPressed('p'))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Pause \n");

    actions[Pause] = ic::REGISTERED;
  }
  if (InputManager::ButtonPressed(ic::X) || InputManager::ButtonPressed(ic::Y)
      || InputManager::KeyPressed('f'))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Attack \n");

    actions[Attack] = ic::REGISTERED;
  }
  if (InputManager::ButtonPressed(ic::DUP) || InputManager::ButtonHeld(ic::DUP)
      || InputManager::KeyPressed(ic::ArrowKeys::UP) || InputManager::KeyHeld(ic::ArrowKeys::UP) ||
      InputManager::GetAxis(ic::Axes::LEFTY) < 0.f)
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Up \n");

    actions[Up] = ic::REGISTERED;
  }

  if (InputManager::ButtonPressed(ic::A) || InputManager::ButtonPressed(ic::B)
      || InputManager::KeyPressed(ic::ArrowKeys::UP))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Jump \n");

    actions[Jump] = ic::REGISTERED;
  }

  if (InputManager::ButtonPressed(ic::DDOWN) || InputManager::KeyPressed(ic::ArrowKeys::DOWN)
      || InputManager::GetAxis(ic::Axes::LEFTY) > 0.f || InputManager::KeyPressed(ic::ArrowKeys::DOWN))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Down \n");

    actions[Down] = ic::REGISTERED;
  }
  if (InputManager::ButtonPressed(ic::DRIGHT) || InputManager::KeyPressed(ic::ArrowKeys::RIGHT)
      || InputManager::KeyHeld(ic::ArrowKeys::RIGHT) || InputManager::ButtonHeld(ic::DRIGHT)
      || InputManager::GetAxis(ic::Axes::LEFTX) > 0.f || InputManager::KeyPressed(ic::ArrowKeys::RIGHT))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Right \n");

    actions[Right] = ic::REGISTERED;
  }
  if (InputManager::ButtonPressed(ic::DLEFT) || InputManager::ButtonHeld(ic::DLEFT)
      || InputManager::KeyPressed(ic::ArrowKeys::LEFT) || InputManager::GetAxis(ic::Axes::LEFTX) < 0.f
      || InputManager::KeyHeld(ic::ArrowKeys::LEFT))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Left \n");

    actions[Left] = ic::REGISTERED;
  }

  if (actions[Left] || actions[Right])
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Run \n");

    actions[Run] = ic::REGISTERED;

    TraceLogger::Log(TraceLogger::TRACE, "Actions: Move \n");

    actions[Move] = ic::REGISTERED;
  }
  if (!actions[Move] && (actions[Up] || actions[Down]))
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Move \n");

    actions[Move] = ic::REGISTERED;
  }
  if (InputManager::KeyPressed('x') ||
      abs(InputManager::GetAxis(ic::Axes::RIGHTX)) > 0.f
      || abs(InputManager::GetAxis(ic::Axes::RIGHTY)) > 0.f)
  {
    TraceLogger::Log(TraceLogger::TRACE, "Actions: Dash \n");

    actions[Dash] = ic::REGISTERED;
  }

  for (int i = 0; i < ActionAmount; ++i)
  {
    int& curr = actions[i];
    int& prev = prevActions[i];
    switch (curr)
    {
    case ic::REGISTERED:
      switch (prev)
      {
      case ic::PRESSED:
        //fallthrough
      case ic::HELD:
        curr = ic::HELD;
        break;
      case ic::RELEASED:
        //fallthrough
      case ic::NONE:
        curr = ic::PRESSED;
        break;
      }
      break;
    case ic::UNREGISTERED:
      switch (prev)
      {
      case ic::PRESSED:
        //fallthrough
      case ic::HELD:
        curr = ic::RELEASED;
        break;
      default:
        curr = ic::NONE;
      }
      break;
    }
  }
}

} // namespace UWUEngine
