#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Editor.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <UWUEngine/Behaviors/DynamicCamera.h>

namespace cc = CameraConstants;
// Level2
static EntityID sight;
static EntityID perception;
static std::vector<EntityID> objects;
static EntityID stones[3];
static glm::vec4 gravity = { 0, 800.f, 0, 0 };
static float height = static_cast<float>(WindowConstants::WINDOW_HEIGHT);
static float width = static_cast<float>(WindowConstants::WINDOW_WIDTH);

void GameStateMachine::Enter_Level2()
{
  objects = DeserializeLevel("level2");
  //SoundInterface::playSound("background_music");
    Camera::SetCameraPosition({ 0.0f, 0.0f, cc::CAMERA_POSITION });

	int stonecount = 0;

	for (auto i = objects.begin(); i != objects.end(); ++i)
	{
		if (EntityManager::GetType(*i) == EntityManager::Player)
		{
			sight = *i;
		}
		else if (EntityManager::GetType(*i) == EntityManager::Solid)
		{
			stones[stonecount++] = *i;
            //TextureComponentManager::SetColor(*i, { 0.0f,0.0f,0.0f,0.0f });
		}
		else if(EntityManager::GetType(*i) == EntityManager::Perception)
		{
      perception = *i;
			//ShaderModule::Deactivate(*i);
		}
	}

	//ColliderComponentManager::Activate(sight);

    //TODO: serialize dimensions
	TextureComponentManager::SetDimensions({ 4, 2 }, sight);

	auto sight_size = TransformComponentManager::GetScale(sight);
	//ColliderComponentManager::SetHitbox(sight, { ColliderComponentManager::Type::RECTANGLE, {0, 0, sight_size.x / 2, sight_size.y } });
	//AnimationComponentManager::AddNewAnimation(sight, 1);
	//AnimationComponentManager::AddFrame(0, .25f, sight, 1);

	for (int i = 0; i < 3; i++)
	{
		//ColliderComponentManager::Activate(stones[i]);
		//ColliderComponentManager::SetHitbox(stones[i], { ColliderComponentManager::Type::RECTANGLE, stones[i], {0, 0, glm::vec2(TransformComponentManager::GetScale(stones[i]))} });
		//ColliderComponentManager::SetRectangleCollider(stones[i]);
	}
    //Lighting::SetAmbient(2.1f);
    //Lighting::SetSpecular(12.f);
    //Lighting::SetLightColor({ 1.0f,1.0f,1.0f,1.0f });
    //Lighting::SetViewPosition(Camera::GetCameraPosition());
    //Lighting::SetLightPosition({ 1387.f,1303.f,500.0f });

    //EntityID dontlook = EntityManager::New(Type::Player);
    //TextureComponentManager::Activate(dontlook);
    //TextureComponentManager::SetFilePath(dontlook, "./assets/pixel.png");
    //TextureAtlaser::LoadAtlasPage();
    //EntityManager::Destroy(dontlook);
    
    BehaviorComponentManager::Activate(sight);
    BehaviorComponentManager::Activate(perception);
    TextureAtlaser::LoadAtlasPage();
}

void GameStateMachine::Load_Level2()
{
	//objects = DeserializeLevel("level2");
}

void GameStateMachine::Unload_Level2() {}

void GameStateMachine::Update_Level2(float dt)
{

  if (InputManager::KeyPressed('H'))
    PlayerData::Hurt(1);

  if (InputManager::KeyHeld('E'))
    PlayerData::LoseEnergy(2);

  if (InputManager::KeyHeld('Q'))
    PlayerData::GainEnergy(2);

  DynamicCamera::SetTrackingPos(glm::vec4(glm::vec2(TransformComponentManager::GetTranslation(PlayerData::GetPlayerID())) + glm::vec2{0, 100}, Camera::GetCameraPosition().z, 1));
  DynamicCamera::SetTrackingSpeed(3);
  DynamicCamera::SetInnerBounds(100, 100, { 0, 100 });

    Lighting::Change();
    //LightingComponentManager::SetLightState(Type::Background, LC::LIGHT_STATE_ON);
	if (InputManager::KeyPressed('v'))
	{
		SerializeLevel("level2");
	}

	if (InputManager::KeyPressed('r'))
	{
		SetNextState(Restart);
	}

	if (InputManager::KeyPressed('1'))
	{
		SetNextState(Level1);
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

}

void GameStateMachine::Exit_Level2()
{
  DynamicCamera::SetTrackingSpeed(0);
	EntityManager::DestroyAll();
    TextureAtlaser::ClearData();
}