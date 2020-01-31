#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/constants.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Editor.h>
#include <UWUEngine/Deserialization.h>
#include <UWUEngine/Serialization.h>
#include <iomanip>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"

namespace wc = WindowConstants;

// OpenGL KHR DEBUG CALLBACK FUNCTION
void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
  TraceLogger::Log(TraceLogger::ERROR, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
    type, severity, message);
}

// Level1
static inline constexpr int OBJECT_AMOUNT = 50;
static EntityID players[OBJECT_AMOUNT];
static EntityID text, vec;
static EntityID particles;
static EntityID sight;

void GameStateMachine::Load_Level1() { DeserializeLevel("BrayanSBOX"); }
void GameStateMachine::Unload_Level1() {}




void GameStateMachine::Enter_Level1()
{
  if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1))
    TraceLogger::Log(TraceLogger::INFO) << "Joystick is gamepad: " << glfwGetGamepadName(GLFW_JOYSTICK_1) << std::endl;
  if (glfwJoystickIsGamepad(GLFW_JOYSTICK_2))
    TraceLogger::Log(TraceLogger::INFO) << "Joystick is gamepad: " << glfwGetGamepadName(GLFW_JOYSTICK_2) << std::endl;

   EntityFactory::CreateObject(EntityManager::Type::ParticleEmitter);
	for (int i = 0; i < OBJECT_AMOUNT; ++i)
	{
      players[i] = EntityFactory::CreateObject(EntityManager::Type::Cyclone);
		if (i >= 90)
		{
			float rannum_z = Random::Range(-1400.f, 1400.f);
			static float x_pos = -wc::WINDOW_WIDTH;
			TransformComponentManager::SetTranslation({ x_pos, wc::WINDOW_HEIGHT, rannum_z , 1 }, players[i]);
			x_pos += 200.f;
			glm::vec4 gravity = {};
			gravity.y = Random::Range(-600.f, -450.f);
			PhysicsComponentManager::SetVelocity(gravity, players[i]);
		}
		else
		{
			TransformComponentManager::SetTranslation({ -20.f * i, 0, i * 20.f , i }, players[i]);
		}

		TransformComponentManager::SetScale({ 100.f, 100.f , 1 }, players[i]);
		TransformComponentManager::SetRotation(Random::Range(-20.f, 20.f), players[i]);

		PhysicsComponentManager::SetRotationalVelocity(-3.14f, players[i]);
		glm::vec3 ransum = { Random::Range(0.1f, 0.4f),Random::Range(0.5f, 0.9f),Random::Range(0.7f, 0.9f) };
		TextureComponentManager::SetColor(players[i], { ransum.x,ransum.y,ransum.z,1.0f });
	}



    // During init, enable debug output
    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(MessageCallback, 0);
    Camera::SetCameraPosition({ 0.0f,0.0f,3000.f });
    //Lighting::SetAmbient(-2.f);
    //Lighting::SetSpecular(2.f);
    //Lighting::SetLightColor({ 1.0f,1.0f,1.0f,1.0f });
    //Lighting::SetViewPosition(Camera::GetCameraPosition());
    //Lighting::SetLightPosition({ 0.f,1000.0f,500.0f });

    // atlasing stuff
    //EntityID dontlook = EntityManager::New(Type::Player);
    //TextureComponentManager::Activate(dontlook);
    //TextureComponentManager::SetFilePath(dontlook, "./assets/pixel.png");
    //TextureAtlaser::LoadAtlasPage();
    //EntityManager::Destroy(dontlook);
    TextureAtlaser::LoadAtlasPage();
}

void GameStateMachine::Update_Level1(float dt)
{
    //LightingComponentManager::SetLightState(Type::Particle, LC::LIGHT_STATE_ON);
	glm::vec4 movement = {};
	

	for (int i = 0; i < OBJECT_AMOUNT; ++i)
	{
		if (i >= 90)
		{
			if (TransformComponentManager::GetTranslation(players[i]).y <= -wc::WINDOW_HEIGHT)
			{
				glm::vec4 new_pos = TransformComponentManager::GetTranslation(players[i]);
				new_pos.y = wc::WINDOW_HEIGHT;
				new_pos.x = Random::Range(static_cast<float>(-wc::WINDOW_WIDTH), static_cast<float>(wc::WINDOW_WIDTH));
				new_pos.z = Random::Range(-1400.f, 1400.f);
				TransformComponentManager::SetTranslation(new_pos, players[i]);
				glm::vec4 gravity = {};
				gravity.y = Random::Range(-600.f, -450.f);
				PhysicsComponentManager::SetVelocity(gravity, players[i]);
			}
		}
		else
		{
			movement.y += 10.f * i * (!!(InputManager::KeyHeld('s')) - !!(InputManager::KeyHeld('w')));
			movement.x += 10.f * i * (!!(InputManager::KeyHeld('d')) - (!!(InputManager::KeyHeld('a'))));
			PhysicsComponentManager::SetVelocity(movement, players[i]);
		}
	}
	

	if (InputManager::KeyPressed('v'))
	{
		SerializeLevel("level1");
	}

  if (InputManager::KeyPressed('2'))
  {
    SetNextState(Level2);
  }

  if (InputManager::KeyPressed('3'))
  {
    SetNextState(YiPlayGround);
  }
  if (InputManager::KeyPressed('4'))
  {
    SetNextState(BrayanSBOX);
  }
  if (InputManager::KeyPressed('c'))
  {
    Camera::ResetCameraPosition();
  }

  for(int i = ic::A; i < ic::CBCOUNT; ++i)
  {
    if (InputManager::ButtonPressed(i))
      TraceLogger::Log(TraceLogger::TRACE) << "Button Pressed: " << i << std::endl;


    //printf(InputManager::ButtonPressed(i)? "Button Pressed: %d\n" : "",i) ;
    //printf(InputManager::ButtonHeld(i)? "Button Held: %d\n" : "",i) ;
    //printf(InputManager::ButtonReleased(i)? "Button Released: %d\n" : "",i) ;
    //printf("Left XY: %f, %f\n", InputManager::GetAxis(GLFW_JOYSTICK_1, ic::LEFTX),
    //  InputManager::GetAxis(GLFW_JOYSTICK_1, ic::LEFTY));
    //printf("Right XY: %f, %f\n", InputManager::GetAxis(GLFW_JOYSTICK_1, ic::RIGHTX),
    //  InputManager::GetAxis(GLFW_JOYSTICK_1, ic::RIGHTY));
    //printf("Left Trigger: %f\n", InputManager::GetAxis(ic::LT_A, 0 ));
    //printf("Right Trigger: %f\n", InputManager::GetAxis(ic::RT_A, 0));
  }

	// Load the saved state (reinitialize what needs reinitializing)
	if (InputManager::KeyPressed('r'))
	{
		//Engine::editor.Stop();
		EntityManager::DestroyAll();
		std::vector<EntityID> newObjects = DeserializeLevel("level1");

		// While size and 100 (size of players) should be the same thing, it's just safer to make sure

		// TODO: Set up a way to move this into Serialization code
		//GLSLShader shader = ShaderModule::CreateShader("./shaders/pass-thru-pos2d-clr.vert", "./shaders/basic-color.frag");
		//GLuint texture = TextureComponentManager::LoadTexture("./assets/cyclone.png");
		for (int i = 0; i < newObjects.size() && i < OBJECT_AMOUNT; i++)
		{
			players[i] = newObjects[i];
			glm::vec3 ransum = { Random::Range(0.1f, 0.4f),Random::Range(0.5f, 0.9f),Random::Range(0.7f, 0.9f) };
			TextureComponentManager::SetColor(players[i], { ransum.x,ransum.y,ransum.z,1.0f });
		}
	}
  
}

void GameStateMachine::Exit_Level1()
{
	//Engine::editor.Stop();
	EntityManager::DestroyAll();
    TextureAtlaser::ClearData();
}