//Authors: other people and Brayan Lopez
#pragma once

#include <UWUEngine/constants.h>
#include <UWUEngine/BaseSystem.h>
#include <map>
#include <glm/vec2.hpp>
#include <UWUEngine/WindowManager.h>

namespace ic = InputConstants;
class InputManager : public BaseSystem<InputManager>
{
public:

  InputManager();
  ~InputManager() = default;
  void Update() override;
  static void UpdateGamepads();

  static glm::vec2 GetMousePos();
  static glm::vec2 GetScrollWheelVec();

  static bool MousePressed(int key);
  static bool MouseReleased(int key);
  static bool MouseHeld(int key);

  static bool KeyPressed(int key);
  static bool KeyReleased(int key);
  static bool KeyHeld(int key);

  static bool ButtonPressed(int button, int controllerID = GLFW_JOYSTICK_1);
  static bool ButtonReleased(int button, int controllerID = GLFW_JOYSTICK_1);
  static bool ButtonHeld(int button, int controllerID = GLFW_JOYSTICK_1);
  static float GetAxis(ic::Axes axis, int controllerID = GLFW_JOYSTICK_1);
  static glm::vec2 GetJoyAxis(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  static float GetJoyRads(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  static float GetJoyDegs(ic::Axes joystick, int controllerID = GLFW_JOYSTICK_1);
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
  static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
  static void MousePosCallback(GLFWwindow* window, double xPos, double yPos);
  static void ScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
  static void JoystickCallback(int controllerID, int event);
private:
  static void AdvanceMap(std::map<int, ic::InputResult>& map, std::map<int, ic::InputResult>& prevMap);
  static ic::InputResult InputKey(std::map<int, ic::InputResult>& map, int key);
  static void PushInput(std::map<int, ic::InputResult>& map, int key, int action);
  static unsigned char UpdateButton(unsigned char button, unsigned char prevButton);
  static std::map<int, ic::InputResult> keys;
  static std::map<int, ic::InputResult> prevKeys;
  static std::map<int, ic::InputResult> mouse;
  static std::map<int, ic::InputResult> prevMouse;
  static std::map<int, ic::InputResult> prevButtons;
  static std::array<GLFWgamepadstate, MAX_PLAYERS> controllers;
  static std::array<GLFWgamepadstate, MAX_PLAYERS> prevControllers;
  static glm::vec2 mousePos;
  static glm::vec2 scrollVec;
  static glm::vec2 deadzones; // {x, y}
  static glm::vec2 prevMousePos;
};

