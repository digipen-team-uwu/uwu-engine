////////#include <UWUEngine/Engine.h>
////////#include "CollisionDetection.h"
////////#include <UWUEngine/Serialization.h>
////////#include <UWUEngine/constants.h>
////////#include "Level3.h"
////////#include <UWUEngine\Audio\SoundInterface.h>
////////
//////////std::vector<EntityID> objects;
////////static EntityID artwork;
////////static EntityID sight;
////////static const char* filePath;
////////
////////void Level3SetTexture(const char* texture)
////////{
////////  filePath = texture;
////////}
////////
////////void Level3Load()
////////{
////////    //objects = DeserializeLevel("Level3");
////////    
////////#pragma endregion
////////}
////////
////////void Level3StartUp()
////////{
////////    Camera::SetCameraPosition({ 0.0f,0.0f,2000.0f });
////////
////////    artwork = Engine::gameObjectManager.New(EntityManager::Type::Background);
////////    sight = Engine::gameObjectManager.New(EntityManager::Type::Player);
////////
////////    GLSLShader shader = ShaderModule::CreateShader(artwork, "./shaders/pass-thru-pos2d-clr.vert",
////////        "./shaders/basic-color.frag");
////////    ShaderModule::Activate(artwork);
////////    ShaderModule::SetShader(artwork, shader);
////////
////////    shader.Use();
////////    shader.SetUniform("myTexture", 0);
////////    shader.UnUse();
////////
////////    ShaderModule::Activate(sight);
////////    ShaderModule::SetShader(sight, shader);
////////
////////    // send data of texture to glsl shader (only need to set this once)
////////    //shader.Use();
////////    //shader.SetUniform("myTexture", 0);
////////    //
////////    //shader = ShaderModule::CreateShader(sight, "./shaders/pass-thru-pos2d-clr.vert",
////////    //    "./shaders/basic-color.frag");
////////    //shader.UnUse();
////////    shader.Use();
////////    shader.SetUniform("myTexture", 0);
////////    shader.UnUse();
////////
////////#if 1
////////#pragma region artwork_init
////////    TransformComponentManager::Activate(artwork);
////////    TextureComponentManager::Activate(artwork);
////////    MeshComponentManager::Activate(artwork);
////////
////////
////////    TextureComponentManager::SetFilePath(artwork, filePath);
////////    MeshComponentManager::SetMesh(artwork, MeshComponentManager::getSquareMesh());
////////    TextureComponentManager::SetTextureID(artwork, TextureComponentManager::LoadTexture(artwork));
////////    TextureComponentManager::SetDimensions({ 1, 1 }, artwork);
////////    auto textureInfo = TextureComponentManager::GetTextureInfo(artwork);
////////    TransformComponentManager::SetScale({ std::get<0>(textureInfo), std::get<1>(textureInfo), 1 }, artwork);
////////    TransformComponentManager::SetTranslation({ 0, 0, 0.f ,0.0f }, artwork);
////////    //TextureComponentManager::RemoveColor(artwork);
////////
////////#pragma endregion
////////#endif
////////
////////#pragma region player_init
////////    TransformComponentManager::Activate(sight);
////////    TextureComponentManager::Activate(sight);
////////    MeshComponentManager::Activate(sight);
////////
////////
////////    //"./assets/Sight_Idle_SpriteSheet.png"
////////    TextureComponentManager::SetFilePath(sight, "./assets/Sight_Idle_SpriteSheet.png");
////////    MeshComponentManager::SetMesh(sight, MeshComponentManager::getSquareMesh());
////////    TextureComponentManager::SetTextureID(sight, TextureComponentManager::LoadTexture(sight));
////////    TextureComponentManager::SetDimensions({ 3, 1 }, sight);
////////     textureInfo = TextureComponentManager::GetTextureInfo(sight);
////////    TransformComponentManager::SetScale({ std::get<0>(textureInfo)/3, std::get<1>(textureInfo), 1 }, sight);
////////    TransformComponentManager::SetTranslation({ 0, 0, 5.f , 0.0f }, sight);
////////    AnimationComponentManager::Activate(sight);
////////    AnimationComponentManager::AddFrame(0, .15f, sight);
////////    AnimationComponentManager::AddFrame(1, .15f, sight);
////////    AnimationComponentManager::AddFrame(2, .15f, sight);
////////    AnimationComponentManager::SetLooping(true, sight);
////////    AnimationComponentManager::Play(sight);
////////#pragma endregion
////////}
////////
////////void Level3Update()
////////{
////////
////////
////////	if (InputManager::KeyPressed('R'))
////////	{
////////        Engine::gameStatesManager.SetNextState(Restart);
////////	}
////////  
////////  //auto cam_pos = Camera::GetCameraPosition();
////////
////////}
////////
////////void Level3ShutDown()
////////{
////////    Engine::gameObjectManager.DestroyAll();
////////}
////////
////////void Level3Unload()
////////{
////////
////////}
//
//#include <spine/Animation.h>
//#include <spine/spine.h>
