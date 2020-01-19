#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/GameStatesManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>

// LogoScene
static EntityID logo;

void GameStateMachine::Load_Logo() {}

void GameStateMachine::Unload_Logo() {}

void GameStateMachine::Enter_Logo()
{
	logo = EntityFactory::CreateObject(EntityManager::Type::Logo_);
	//logo = EntityManager::New(EntityManager::Type::Logo);

  GLSLShader shader = ShaderModule::GetEntityShader();
	//ShaderModule::Activate(logo);
	//ShaderModule::SetShader(logo, shader);

	shader.Use();
	shader.SetUniform("myTexture", 0);
	shader.UnUse();

	//MeshComponentManager::Activate(logo);
	//MeshComponentManager::SetMesh(logo, MeshComponentManager::getSquareMesh());

	//TextureComponentManager::Activate(logo);
	//TextureComponentManager::SetFilePath(logo, "./assets/DigiPen_RED_1024px.png");
	//TextureComponentManager::SetTextureID(logo, TextureComponentManager::LoadTexture(logo));

	TransformComponentManager::Activate(logo);
	TransformComponentManager::SetTranslation({ 0.0f,0.0f,0.0f,1 }, logo);
	TransformComponentManager::SetScale({ 1.f,247.f / 1024.f,1 }, logo);
}

void GameStateMachine::Update_Logo(float dt)
{
	static float time = 8.0f;

	GLSLShader shader = ShaderModule::GetEntityShader();

	glm::vec4 color = TextureComponentManager::GetColor(logo);

	color.w -= dt / 3.f;

	time -= dt;

	TextureComponentManager::SetColor(logo, color);

	if (time <= 0.0f || InputManager::KeyPressed(GLFW_KEY_SPACE))
	{
		SetNextState(Level1);
	}
}

void GameStateMachine::Exit_Logo()
{
	EntityManager::DestroyAll();
}