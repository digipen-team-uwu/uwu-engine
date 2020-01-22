#include <UWUEngine/WindowManager.h>
#include <UWUEngine/Event/Event.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Editor.h>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Graphics/Texture/TextureLoader.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <UWUEngine/UI/UIManager.h>
#include <UWUEngine/UI/HUDManager.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>
#include <UWUEngine/Debugs/DebugManager.h>
#include <UWUEngine/Graphics/Camera.h>
#include <UWUEngine/Graphics/Render.h>
#include <UWUEngine/Input/ActionManager.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Audio/SoundInterface.h>

#pragma region Systems
template<>
int RegisterSystemHelper<TraceLogger>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<TraceLogger>(SystemInitOrder::Trace, SystemUpdateOrder::LAST);

template<>
int RegisterSystemHelper<Random>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Random>(SystemInitOrder::FIRST, SystemUpdateOrder::FIRST);

template<>
int RegisterSystemHelper<SoundInterface>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<SoundInterface>(SystemInitOrder::FIRST, SystemUpdateOrder::FIRST);

template<>
int RegisterSystemHelper<EventSystem>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EventSystem>(SystemInitOrder::Event, SystemUpdateOrder::Event);

template<>
int RegisterSystemHelper<FrameRateController>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<FrameRateController>(SystemInitOrder::FIRST, SystemUpdateOrder::FrameRate);

template<>
int RegisterSystemHelper<Editor>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Editor>(SystemInitOrder::Editor, SystemUpdateOrder::Editor);

template<>
int RegisterSystemHelper<EntityManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityManager>(SystemInitOrder::Entity, SystemUpdateOrder::Entity);

template<>
int RegisterSystemHelper<TextureLoader>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<TextureLoader>(SystemInitOrder::TexLoad, SystemUpdateOrder::TexLoad);

template<>
int RegisterSystemHelper<TextureAtlaser>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<TextureAtlaser>(SystemInitOrder::Atlas, SystemUpdateOrder::Atlas);

template<>
int RegisterSystemHelper<EntityVectorManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityVectorManager>(SystemInitOrder::EntityVec, SystemUpdateOrder::EntityVec);

template<>
int RegisterSystemHelper<UIManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<UIManager>(SystemInitOrder::UI, SystemUpdateOrder::UI);

template<>
int RegisterSystemHelper<HUDManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<HUDManager>(SystemInitOrder::HUD, SystemUpdateOrder::HUD);

template<>
int RegisterSystemHelper<Lighting>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Lighting>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

template<>
int RegisterSystemHelper<DebugManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<DebugManager>(SystemInitOrder::LAST, SystemUpdateOrder::Debug);

template<>
int RegisterSystemHelper<TimerManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<TimerManager>(SystemInitOrder::FIRST, SystemUpdateOrder::FIRST);

template<>
int RegisterSystemHelper<Camera>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Camera>(SystemInitOrder::FIRST, SystemUpdateOrder::Camera);

template<>
int RegisterSystemHelper<Render>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<Render>(SystemInitOrder::Render, SystemUpdateOrder::Render);

template<>
int RegisterSystemHelper<ActionManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<ActionManager>(SystemInitOrder::Action, SystemUpdateOrder::Action);

template<>
int RegisterSystemHelper<InputManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<InputManager>(SystemInitOrder::Input, SystemUpdateOrder::Input);

template<>
int RegisterSystemHelper<WindowManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<WindowManager>(SystemInitOrder::Window, SystemUpdateOrder::Window);

template<>
int RegisterSystemHelper<UniformBuffer>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<UniformBuffer>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

#pragma endregion 

#pragma region Components
template<>
size_t RegisterComponentHelper<AnimationComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<AnimationComponentManager>(ComponentUpdateOrder::Animation);

template<>
size_t RegisterComponentHelper<SpineAnimationComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<SpineAnimationComponentManager>(ComponentUpdateOrder::LAST);

template<>
size_t RegisterComponentHelper<SpineSkeletonComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<SpineSkeletonComponentManager>(ComponentUpdateOrder::SpineSkeleton);

template<>
size_t RegisterComponentHelper<BehaviorComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<BehaviorComponentManager>(ComponentUpdateOrder::Behavior);

template<>
size_t RegisterComponentHelper<PhysicsComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<PhysicsComponentManager>(ComponentUpdateOrder::Physics);

template<>
size_t RegisterComponentHelper<ColliderComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<ColliderComponentManager>(ComponentUpdateOrder::Collider);


#pragma endregion 