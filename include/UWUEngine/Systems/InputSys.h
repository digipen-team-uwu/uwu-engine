//Authors: other people and Brayan Lopez
#pragma once

#include <UWUEngine/constants.h>
#include <UWUEngine/System.h>
#include <map>
#include <array>
#include <glm/vec2.hpp>
#include <UWUEngine/Systems/WindowSys.h>
#include <UWUEngine/CCallbackHelper.h>

namespace ic = InputConstants;

namespace UWUEngine
{

class InputSys : public System
{
public:

  InputSys(ISpace*);
  ~InputSys() = default;
  void Update() override;
  void UpdateGamepads();

  glm::vec2 GetMousePos();
  glm::vec2 GetScrollWheelVec();

  bool MousePressed(int key);
  bool MouseReleased(int key);
  bool MouseHeld(int key);

  bool KeyPressed(int key);
  bool KeyReleased(int key);
  bool KeyHeld(int key);

  bool ButtonPressed(int button, int controllerID = GLFW_JOYSTICK_1);
  bool ButtonReleased(int button, int controllerID = GLFW_JOYSTICK_1);
  bool ButtonHeld(int button, int controllerID = GLFW_JOYSTICK_1);
  float GetAxis(ic::Axes axis, int controllerID = GLFW_JOYSTICK_1);
  glm::vec2 GetJoyAxis(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  float GetJoyRads(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  float GetJoyDegs(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
  void MouseCallback(GLFWwindow* window, int button, int action, int mods);
  void MousePosCallback(GLFWwindow* window, double xPos, double yPos);
  void ScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
  void JoystickCallback(int controllerID, int event);
private:
  void AdvanceMap(std::map<int, ic::InputResult>& map, std::map<int, ic::InputResult>& prevMap);
  ic::InputResult InputKey(std::map<int, ic::InputResult>& map, int key);
  void PushInput(std::map<int, ic::InputResult>& map, int key, int action);
  unsigned char UpdateButton(unsigned char button, unsigned char prevButton);
  std::map<int, ic::InputResult> keys;
  std::map<int, ic::InputResult> prevKeys;
  std::map<int, ic::InputResult> mouse;
  std::map<int, ic::InputResult> prevMouse;
  std::map<int, ic::InputResult> prevButtons;
  std::array<GLFWgamepadstate, MAX_PLAYERS> controllers;
  std::array<GLFWgamepadstate, MAX_PLAYERS> prevControllers;
  glm::vec2 mousePos;
  glm::vec2 prevMousePos;
  glm::vec2 scrollVec;
  glm::vec2 deadzones{ 0.2f, 0.2f }; // {x, y}

  using KeyCallbackFn = void (InputSys::*)(GLFWwindow*, int, int, int, int);
  using KeyCallbackHelper = CCallbackHelper<InputSys, KeyCallbackFn, &InputSys::KeyCallback, void, GLFWwindow*, int, int, int, int>;

  using MouseCallbackFn = void (InputSys::*)(GLFWwindow*, int, int, int);
  using MouseCallbackHelper = CCallbackHelper<InputSys, MouseCallbackFn, &InputSys::MouseCallback, void, GLFWwindow*, int, int, int>;

  using MousePosCallbackFn = void (InputSys::*)(GLFWwindow*, double, double);
  using MousePosCallbackHelper = CCallbackHelper<InputSys, MousePosCallbackFn, &InputSys::MousePosCallback, void, GLFWwindow*, double, double>;

  using ScrollWheelCallbackFn = void (InputSys::*)(GLFWwindow*, double, double);
  using ScrollWheelCallbackHelper = CCallbackHelper<InputSys, ScrollWheelCallbackFn, &InputSys::ScrollWheelCallback, void, GLFWwindow*, double, double>;

  using JoystickCallbackFn = void (InputSys::*)(int, int);
  using JoystickCallbackHelper = CCallbackHelper<InputSys, JoystickCallbackFn, &InputSys::JoystickCallback, void, int, int>;
};

} // namespace UWUEngine
