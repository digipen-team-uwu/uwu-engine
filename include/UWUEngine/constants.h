#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <iostream>

//#define THREADED

typedef unsigned int EntityID;

namespace DebugConstants
{
  constexpr bool SHOW_VELOCITY = false;
  constexpr char VELOCITY_KEY = 'L';
}

namespace SerializationConstants
{
  constexpr const char *JSON_PATH = "./data";
}

namespace UIConstants
{
  constexpr glm::uvec2 FONTSHEET_SIZE = { 16, 6 };
}

namespace InputConstants
{
    #define MAX_PLAYERS 1

    enum InputResult {
         RELEASED, PRESSED, HELD, NONE, RESULTCOUNT,
    };

    enum ActionRead
    {
      UNREGISTERED,
      REGISTERED
    };

    enum Mouse {
        LEFT_CLICK = 0, MIDDLE_CLICK = 2, RIGHT_CLICK = 1
    };

    enum ArrowKeys{
        LEFT = 263, RIGHT = 262, UP = 265, DOWN = 264
    };

    enum Buttons
    {
      //actual buttons
      A = GLFW_GAMEPAD_BUTTON_A,
      B = GLFW_GAMEPAD_BUTTON_B,
      X = GLFW_GAMEPAD_BUTTON_X,
      Y = GLFW_GAMEPAD_BUTTON_Y,
      LB = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
      RB = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
      BACK = GLFW_GAMEPAD_BUTTON_BACK,
      START = GLFW_GAMEPAD_BUTTON_START,
      GUIDE = GLFW_GAMEPAD_BUTTON_GUIDE, //maybe this is a ps4 only thing because it doesnt exist on my xbox controller
      LTHUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
      RTHUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
      DUP = GLFW_GAMEPAD_BUTTON_DPAD_UP,
      DRIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
      DDOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
      DLEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
      //virtual buttons
      LT_B, //left trigger
      RT_B, //right trigger
      //bookkeeping
      BUTTONSAMOUNT = LT_B, //max number of buttons supported on controller
      BUTTONS2AMOUNT = 2,   //amount of "buttons" assigned to the virtual buttons array
      CBCOUNT = BUTTONSAMOUNT + BUTTONS2AMOUNT, //total amount of buttons (actual + virtual)
      LT_INDEX = A, //index of virtual button in virtual buttons array, should only be used by InputManager!!
      RT_INDEX = B  //index of virtual button in virtual buttons array, should only be used by InputManager!!
    };

    enum Axes
    {
      LEFTX = GLFW_GAMEPAD_AXIS_LEFT_X,
      LEFTY = GLFW_GAMEPAD_AXIS_LEFT_Y,
      RIGHTX = GLFW_GAMEPAD_AXIS_RIGHT_X,
      RIGHTY = GLFW_GAMEPAD_AXIS_RIGHT_Y,
      LT_A = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
      RT_A = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
      CACOUNT, //axes count on controller
      LEFTJ,   //left joystick
      RIGHTJ   //right joystick
    };

    constexpr float SCROLL_RATE = 0.8f;
    constexpr float SCROLL_FRICTION = 20.f;
    constexpr float MAX_SCROLL = 20.f;
}

namespace WindowConstants
{
    constexpr int WINDOW_HEIGHT = 900;
    constexpr int WINDOW_WIDTH = 1600;
    constexpr float FPS_CAL_DELAY = 1.0;
}

namespace CameraConstants
{
    constexpr float ASPECT_RATIO = static_cast<float>(WindowConstants::WINDOW_WIDTH) / static_cast<float>(WindowConstants::WINDOW_HEIGHT);
    constexpr float ZOOM_FACTOR = 50.f;
    constexpr float CAMERA_POSITION = 2074.f;//static_cast<float>(WindowConstants::WINDOW_HEIGHT) * 2.5f;
}

namespace GameObjectConstants
{
  constexpr unsigned int MAX_SPRITES = 8;
  constexpr unsigned int INITIAL_OBJECT_COUNT = 0;
  constexpr unsigned int INVALID_ID = static_cast<unsigned int>(-1);
}

namespace Vec4Constants
{
    constexpr float POINT = 1.0;
    constexpr float VECTOR = 0.0;
}

namespace StateMachineConsts
{
	constexpr int _STATE_RESTART = -2;
	constexpr int _STATE_INVALID = -1;
	constexpr int _STATE_INITIAL = 0;
}

namespace ParticleSystemConstants
{
  constexpr glm::vec4 UNUSED_VEC4{ static_cast<unsigned int>(-1), 0, 0, 0};
  constexpr glm::vec3 UNUSED_VEC3{ static_cast<unsigned int>(-1), 0, 0};
  constexpr glm::vec2 UNUSED_VEC2{ static_cast<unsigned int>(-1), 0};
  constexpr float UNUSED_FLOAT = static_cast<float>(-1);
}

namespace TextureAtlasing
{
    constexpr bool allow_flip = false;
    constexpr int MAX_SIZE_PAGE = 4096; // 8192
    constexpr unsigned MAX_LAYERS = 7;
    constexpr size_t INVALID_VAO_KEY = static_cast<unsigned int>(-1);
    constexpr unsigned INVALID_LAYER = static_cast<unsigned int>(-1);
    constexpr int SIZE_OFFSET = 2;
    constexpr int OFFSET_OFFSET = 1;
}

namespace LightingConstant
{
    constexpr int LIGHT_STATE_ON = 1;
    constexpr int LIGHT_STATE_OFF = 0;
}

namespace PhysicsConstants
{
    constexpr glm::vec4 gravity = { 0, 800.f, 0, 0 };
}

namespace CodeConstants
{
  constexpr int DEPRECATED = 0;
  constexpr int ACTIVE = 1;
}

namespace UniformBufferConstants
{
    constexpr size_t MEMORY_LAYOUT_OFFSET = sizeof(float);
}