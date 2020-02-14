/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       InputSys.cpp
  \author     Hadi Alhussieni, Brayan Lopez
  \date       2019/10/06
  \brief      Implementation of input managing system for mouse and keyboard input

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Systems/InputSys.h>
#include <UWUEngine/Systems/LogSys.h>
#include <UWUEngine/Systems/FrameLimiterSys.h>
#include <UWUEngine/Helper.h>
#include <UWUEngine/EngineSettings.h>

#include <cctype>
#include <array>

#include <imgui.h>
#include <imgui_impl_glfw.h>

namespace ic = InputConstants;

namespace UWUEngine
{

InputSys::InputSys(ISpace* p) : System(p)
{
  KeyCallbackHelper         bind_key(this);
  MouseCallbackHelper       bind_mouse(this);
  MousePosCallbackHelper    bind_mouse_pos(this);
  ScrollWheelCallbackHelper bind_scroll_wheel(this);
  JoystickCallbackHelper    bind_joystick(this);

  glfwSetKeyCallback(Get<WindowSys>().getWindowHandle(), KeyCallbackHelper::CCallback);
  glfwSetMouseButtonCallback(Get<WindowSys>().getWindowHandle(), MouseCallbackHelper::CCallback);
  glfwSetCursorPosCallback(Get<WindowSys>().getWindowHandle(), MousePosCallbackHelper::CCallback);
  glfwSetScrollCallback(Get<WindowSys>().getWindowHandle(), ScrollWheelCallbackHelper::CCallback);
  glfwSetJoystickCallback(JoystickCallbackHelper::CCallback);
}

void InputSys::PushInput(std::map<int, ic::InputResult>& map, int key, int action)
{
  key = toupper(key);
  if (action == GLFW_PRESS)
  {
    map[key] = ic::InputResult::PRESSED;
  }
  else if (action == GLFW_RELEASE)
  {
    map[key] = ic::InputResult::RELEASED;
  }
}

void InputSys::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
  if (EngineSettings::Editor)
  {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mod);
    if (ImGui::GetIO().WantCaptureKeyboard)
    {
      return;
    }
  }
  if (action != GLFW_REPEAT)
    PushInput(keys, key, action);
}

void InputSys::MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
  if (EngineSettings::Editor)
  {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    if (ImGui::GetIO().WantCaptureMouse)
    {
      return;
    }
  }
  PushInput(mouse, button, action);
}

void InputSys::MousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
  prevMousePos = mousePos;
  mousePos.x = static_cast<float>(xPos);
  mousePos.y = static_cast<float>(yPos);

  //if (Get<CameraSys>().getState() == CameraSys::state::ENABLE_FPS)
  //{
  //  if (Get<CameraSys>().getFirstFlag())
  //  {
  //    prevMousePos = mousePos;
  //    Get<CameraSys>().setFirstFlag(false);
  //  }
  //  const float xOffset = static_cast<float>(xPos) - prevMousePos.x;
  //  const float yOffset = prevMousePos.y - static_cast<float>(yPos); // y go from bottom to top

  //  Get<CameraSys>().mouseMovement(xOffset, yOffset);
  //}
}

void InputSys::ScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
{
  if (EngineSettings::Editor)
  {
    ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
    if (ImGui::GetIO().WantCaptureMouse)
    {
      return;
    }
  }
  scrollVec.x = static_cast<float>(xOffset);
  if (scrollVec.y < ic::MAX_SCROLL && scrollVec.y > -ic::MAX_SCROLL)
    scrollVec.y += static_cast<float>(yOffset)* ic::SCROLL_RATE;
}

void InputSys::JoystickCallback(int controllerID, int event)
{
  if (event == GLFW_CONNECTED)
  {
    // The joystick was connected
    Get<LogSys>().Log(Get<LogSys>().INFO, "Joystick: %d was connected\n", controllerID);
  }
  else if (event == GLFW_DISCONNECTED)
  {
    // The joystick was disconnected
    Get<LogSys>().Log(Get<LogSys>().INFO, "Joystick: %d was disconnected\n", controllerID);
  }
}

bool InputSys::MousePressed(int key)
{
  return ic::InputResult::PRESSED == InputKey(mouse, key);
}

bool InputSys::MouseReleased(int key)
{
  return ic::InputResult::RELEASED == InputKey(mouse, key);
}

bool InputSys::MouseHeld(int key)
{
  return ic::InputResult::HELD == InputKey(mouse, key);
}

bool InputSys::KeyPressed(int key)
{
  key = toupper(key);
  return ic::InputResult::PRESSED == InputKey(keys, key);
}

bool InputSys::KeyReleased(int key)
{
  key = toupper(key);
  return ic::InputResult::RELEASED == InputKey(keys, key);
}

bool InputSys::KeyHeld(int key)
{
  key = toupper(key);
  return ic::InputResult::HELD == InputKey(keys, key);
}

bool InputSys::ButtonPressed(int button, int controllerID)
{
  if (button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::PRESSED;
}

bool InputSys::ButtonReleased(int button, int controllerID)
{
  if (button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::RELEASED;
}

bool InputSys::ButtonHeld(int button, int controllerID)
{
  if (button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::HELD;
}

float InputSys::GetAxis(ic::Axes axis, int controllerID)
{
  return controllers[controllerID].axes[axis];
}

glm::vec2 InputSys::GetJoyAxis(ic::Axes joystick, int controllerID)
{
  switch (joystick)
  {
  case ic::LEFTJ:
    return glm::vec2(controllers[controllerID].axes[ic::LEFTX], controllers[controllerID].axes[ic::LEFTY]);
  case ic::RIGHTJ:
    return glm::vec2(controllers[controllerID].axes[ic::RIGHTX], controllers[controllerID].axes[ic::RIGHTY]);
  default:
    return glm::vec2(0.f);
  }
}

float InputSys::GetJoyRads(ic::Axes joystick, int controllerID)
{
  switch (joystick)
  {
  case ic::LEFTJ:
    return RotationFromVec(glm::vec4(controllers[controllerID].axes[ic::LEFTX], -controllers[controllerID].axes[ic::LEFTY], 0.f, 0.f));
  case ic::RIGHTJ:
    return RotationFromVec(glm::vec4(controllers[controllerID].axes[ic::RIGHTX], -controllers[controllerID].axes[ic::RIGHTY], 0.f, 0.f));
  default:
    return 0.f;
  }
}

float InputSys::GetJoyDegs(ic::Axes joystick, int controllerID)
{
  return glm::degrees(GetJoyRads(joystick, controllerID));
}

ic::InputResult InputSys::InputKey(std::map<int, ic::InputResult>& map, int key)
{
  auto result = map.find(key);
  if (result != map.end())
  {
    return result->second;
  }
  return ic::InputResult::NONE;
}

void InputSys::Update()
{
  glfwPollEvents();
  UpdateGamepads();
  if (scrollVec.y > 0)
  {
    scrollVec.y -= Get<FrameLimiterSys>().GetDeltaTime<float>() * ic::SCROLL_FRICTION;
    if (scrollVec.y < 0)
    {
      scrollVec.y = 0;
    }
  }
  else if (InputSys::scrollVec.y < 0)
  {
    scrollVec.y += Get<FrameLimiterSys>().GetDeltaTime<float>() * ic::SCROLL_FRICTION;
    if (scrollVec.y > 0)
    {
      scrollVec.y = 0;
    }
  }

  AdvanceMap(keys, prevKeys);
  AdvanceMap(mouse, prevMouse);
}

void InputSys::UpdateGamepads()
{
  prevControllers.swap(controllers);

  for (unsigned i = 0; i < controllers.size(); ++i)
  {
    auto& controller = controllers[i];
    auto& axes = controller.axes;
    glfwGetGamepadState(i, &controller);
    //controller.buttons2[ic::Buttons::LT_INDEX] = axes[ic::Axes::LT_A] >= -.75f;
    //controller.buttons2[ic::Buttons::RT_INDEX] = axes[ic::Axes::RT_A] >= -.75f;
      //TODO::Remove all existence of GLFWgamepadstate.buttons2
    if (abs(axes[ic::Axes::LEFTX]) < deadzones.x)
    {
      axes[ic::Axes::LEFTX] = 0.f;
    }
    if (abs(axes[ic::Axes::LEFTY]) < deadzones.y)
    {
      axes[ic::Axes::LEFTY] = 0.f;
    }
    if (abs(axes[ic::Axes::RIGHTX]) < deadzones.x)
    {
      axes[ic::Axes::RIGHTX] = 0.f;
    }
    if (abs(axes[ic::Axes::RIGHTY]) < deadzones.y)
    {
      axes[ic::Axes::RIGHTY] = 0.f;
    }

  }

  for (unsigned i = 0; i < MAX_PLAYERS; ++i)
  {
    for (int j = 0; j < ic::BUTTONSAMOUNT; ++j)
    {
      auto& currButton = controllers[i].buttons[j];
      auto& prevButton = prevControllers[i].buttons[j];
      currButton = UpdateButton(currButton, prevButton);
    }

    for (int j = 0; j < ic::BUTTONS2AMOUNT; ++j)
    {
      //auto& currButton = controllers[i].buttons2[j];
      //auto& prevButton = prevControllers[i].buttons2[j];
      //currButton = UpdateButton(currButton, prevButton);
        //TODO::Remove all existence of GLFWgamepadstate.buttons2
    }
  }

}

unsigned char InputSys::UpdateButton(unsigned char button, unsigned char prevButton)
{
  switch (button)
  {
  case 0: //0 means button was not pressed this frame
    switch (prevButton)
    {
    case ic::HELD:
      //fallthrough
    case ic::PRESSED:
      button = ic::RELEASED;
      break;
    default:
      button = ic::NONE;
    }
    break;
  case 1: //1 means button was pressed this frame
    switch (prevButton)
    {
    case ic::NONE:
      //fallthrough
    case ic::RELEASED:
      button = ic::PRESSED;
      break;
    case ic::PRESSED:
      //fallthrough
    case ic::HELD:
      button = ic::HELD;
      break;
    }
    break;
  }
  return button;
}

void InputSys::AdvanceMap(std::map<int, ic::InputResult>& map, std::map<int, ic::InputResult>& prevMap)
{
  prevMap.swap(map);
  map.clear();

  for (auto it = prevMap.begin(); it != prevMap.end(); ++it)
  {
    ic::InputResult lastState = it->second;

    if (lastState == ic::InputResult::PRESSED || lastState == ic::InputResult::HELD)
    {
      map[it->first] = ic::InputResult::HELD;
    }
    else if (lastState == ic::InputResult::RELEASED)
    {
      map[it->first] = ic::InputResult::NONE;
    }
  }
}

glm::vec2 InputSys::GetMousePos()
{
  return mousePos;
}

glm::vec2 InputSys::GetScrollWheelVec()
{
  return scrollVec;
}

} // namespace UWUEngine
