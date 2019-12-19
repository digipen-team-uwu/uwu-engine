/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       InputManager.cpp
  \author     Hadi Alhussieni, Brayan Lopez
  \date       2019/10/06
  \brief      Implementation of input managing system for mouse and keyboard input

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Input/InputManager.h>
#include <cctype>
#include <UWUEngine/FrameRateController.h>
#include <iostream>
#include <array>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Helper.h>

namespace ic = InputConstants;

template<>
int RegisterSystemHelper<InputManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<InputManager>(SystemInitOrder::Input, SystemUpdateOrder::Input);

//TODO: make drag and drop callback for dragging pictures and jsons
//TODO::Remove all existence of GLFWgamepadstate.buttons2

std::map<int, ic::InputResult> InputManager::keys;
std::map<int, ic::InputResult> InputManager::prevKeys;
std::map<int, ic::InputResult> InputManager::mouse;
std::map<int, ic::InputResult> InputManager::prevMouse;
std::map<int, ic::InputResult> InputManager::prevButtons;
std::array<GLFWgamepadstate, MAX_PLAYERS> InputManager::controllers;
std::array<GLFWgamepadstate, MAX_PLAYERS> InputManager::prevControllers;
glm::vec2 InputManager::mousePos = {};
glm::vec2 InputManager::scrollVec = {};
glm::vec2 InputManager::deadzones{0.2f, 0.2f};

InputManager::InputManager()
{
  glfwSetKeyCallback(WindowManager::getWindowHandle(), KeyCallback);
  glfwSetMouseButtonCallback(WindowManager::getWindowHandle(), MouseCallback);
  glfwSetCursorPosCallback(WindowManager::getWindowHandle(), MousePosCallback);
  glfwSetScrollCallback(WindowManager::getWindowHandle(), ScrollWheelCallback);
  glfwSetJoystickCallback(JoystickCallback);
}

void InputManager::PushInput(std::map<int, ic::InputResult> &map, int key, int action)
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

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
  if (action != GLFW_REPEAT)
    PushInput(keys, key, action);
}

void InputManager::MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
  PushInput(mouse, button, action);
}

void InputManager::MousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
  mousePos.x = static_cast<float>(xPos);
  mousePos.y = static_cast<float>(yPos);
}

void InputManager::ScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
{
  scrollVec.x = static_cast<float>(xOffset);
  if(scrollVec.y < ic::MAX_SCROLL && scrollVec.y > -ic::MAX_SCROLL)
    scrollVec.y += static_cast<float>(yOffset) * ic::SCROLL_RATE;
}

void InputManager::JoystickCallback(int controllerID, int event)
{
  if (event == GLFW_CONNECTED)
  {
    // The joystick was connected
    TraceLogger::Log(TraceLogger::INFO, "Joystick: %d was connected\n", controllerID);
  }
  else if (event == GLFW_DISCONNECTED)
  {
    // The joystick was disconnected
    TraceLogger::Log(TraceLogger::INFO, "Joystick: %d was disconnected\n", controllerID);
  }
}

bool InputManager::MousePressed(int key)
{
  return ic::InputResult::PRESSED == InputKey(mouse, key);
}

bool InputManager::MouseReleased(int key)
{
  return ic::InputResult::RELEASED == InputKey(mouse, key);
}

bool InputManager::MouseHeld(int key)
{
  return ic::InputResult::HELD == InputKey(mouse, key);
}

bool InputManager::KeyPressed(int key)
{
  key = toupper(key);
  return ic::InputResult::PRESSED == InputKey(keys, key);
}

bool InputManager::KeyReleased(int key)
{
  key = toupper(key);
  return ic::InputResult::RELEASED == InputKey(keys, key);
}

bool InputManager::KeyHeld(int key)
{
  key = toupper(key);
  return ic::InputResult::HELD == InputKey(keys, key);
}

bool InputManager::ButtonPressed(int button, int controllerID)
{
  if(button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::PRESSED;
  //return controllers[controllerID].buttons2[button - ic::BUTTONSAMOUNT] == ic::InputResult::PRESSED;
    //TODO::Remove all existence of GLFWgamepadstate.buttons2
}

bool InputManager::ButtonReleased(int button, int controllerID)
{
  if (button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::RELEASED;
  //return controllers[controllerID].buttons2[button - ic::BUTTONSAMOUNT] == ic::InputResult::RELEASED;
    //TODO::Remove all existence of GLFWgamepadstate.buttons2
}

bool InputManager::ButtonHeld(int button, int controllerID)
{
  if (button < ic::BUTTONSAMOUNT)
    return controllers[controllerID].buttons[button] == ic::InputResult::HELD;
  //return controllers[controllerID].buttons2[button - ic::BUTTONSAMOUNT] == ic::InputResult::HELD;
    //TODO::Remove all existence of GLFWgamepadstate.buttons2
}

float InputManager::GetAxis(ic::Axes axis, int controllerID)
{
  return controllers[controllerID].axes[axis];
}

glm::vec2 InputManager::GetJoyAxis(ic::Axes joystick, int controllerID)
{
  switch(joystick)
  {
    case ic::LEFTJ:
      return glm::vec2(controllers[controllerID].axes[ic::LEFTX], controllers[controllerID].axes[ic::LEFTY]);
    case ic::RIGHTJ:
      return glm::vec2(controllers[controllerID].axes[ic::RIGHTX], controllers[controllerID].axes[ic::RIGHTY]);
    default:
      return glm::vec2(0.f);
  }
}

float InputManager::GetJoyRads(ic::Axes joystick, int controllerID)
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

float InputManager::GetJoyDegs(ic::Axes joystick, int controllerID)
{
  return glm::degrees(GetJoyRads(joystick, controllerID));
}

ic::InputResult InputManager::InputKey(std::map<int, ic::InputResult>& map, int key)
{
  auto result = map.find(key);
  if (result != map.end())
  {
    return result->second;
  }
  return ic::InputResult::NONE;
}

void InputManager::Update()
{
  UpdateGamepads();
  if (InputManager::scrollVec.y > 0)
  {
    InputManager::scrollVec.y -= FrameRateController::GetDeltaTime<float>() * ic::SCROLL_FRICTION;
    if (InputManager::scrollVec.y < 0)
      InputManager::scrollVec.y = 0;
  }
  else if(InputManager::scrollVec.y < 0)
  {
    InputManager::scrollVec.y += FrameRateController::GetDeltaTime<float>() * ic::SCROLL_FRICTION;
    if (InputManager::scrollVec.y > 0)
      InputManager::scrollVec.y = 0;
  }

  AdvanceMap(keys, prevKeys);
  AdvanceMap(mouse, prevMouse);
}

void InputManager::UpdateGamepads()
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
    
  for(unsigned i = 0; i < MAX_PLAYERS; ++i)
  {
    for(int j = 0; j < ic::BUTTONSAMOUNT; ++j)
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

unsigned char InputManager::UpdateButton(unsigned char button, unsigned char prevButton)
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

void InputManager::AdvanceMap(std::map<int, ic::InputResult>& map, std::map<int, ic::InputResult>& prevMap)
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

glm::vec2 InputManager::GetMousePos()
{
  return mousePos;
}

glm::vec2 InputManager::GetScrollWheelVec()
{
  return scrollVec;
}

//DEPRECATED
/* 
int InputManager::Update()
{
    int count = 0;
    SDL_Event event;
    prevKeys = keys;
    
    while (SDL_PollEvent(&event))
    {
        ++count;
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym >= SDLK_RIGHT)
            {
                keys[event.key.keysym.sym + ic::ARROW_OFFSET] = true;
            }
            keys[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym >= SDLK_RIGHT)
            {
                keys[event.key.keysym.sym + ic::ARROW_OFFSET] = false;
            }
            keys[event.key.keysym.sym] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            keys[event.button.button + ic::MOUSE_OFFSET] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            keys[event.button.button + ic::MOUSE_OFFSET] = false;
            break;
        case SDL_MOUSEMOTION:
            mouse = { event.motion.xrel, -event.motion.yrel };
            break;
        case SDL_QUIT:
            exit = true;
            break;
        }
    }
    return count;
}

ic::InputResult InputManager::InputKey(char key) const
{
    const auto prev = prevKeys.find(tolower(key));
    const auto current = keys.find(tolower(key));    

    if (current == keys.end())
    {
        return ic::InputResult::NONE;
    }

    if (current->second && (prev == prevKeys.end() || !(prev->second)))
    {
        return ic::InputResult::PRESSED;
    }

    if (!(current->second) && (prev != prevKeys.end() && prev->second))
    {
        return ic::InputResult::RELEASED;
    }

    if (current->second)
    {
        return ic::InputResult::HELD;
    }
    return ic::InputResult::NONE;
}
*/
