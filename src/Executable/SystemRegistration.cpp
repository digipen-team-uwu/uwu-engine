#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <UWUEngine/Component/AnimationComponentManager.h>
#include <UWUEngine/Component/ColliderComponentManager.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/SpineSkeletonComponentManager.h>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>

#include <UWUEngine/Scene/SceneManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/Event/Event.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Editor.h>
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
#include <UWUEngine/Graphics/Shader/UniformBufferSystem.h>
#include <UWUEngine/DragAndDrop.h>

#pragma region Systems
//Register
RegisterSystem(SceneManager, SceneManager, SceneManager)
RegisterSystem(TraceLogger, Trace, LAST)
RegisterSystem(Random, FIRST, FIRST)
RegisterSystem(SoundInterface, FIRST, FIRST)
RegisterSystem(EventSystem, Event, Event)
RegisterSystem(FrameRateController, FIRST, FrameRate)
RegisterSystem(Editor, Editor, Editor)
RegisterSystem(EntityManager, Entity, Entity)
RegisterSystem(TextureLoader, TexLoad, TexLoad)
RegisterSystem(TextureAtlaser, Atlas, Atlas)
RegisterSystem(EntityVectorManager, EntityVec, EntityVec)
RegisterSystem(UIManager, UI, UI)
RegisterSystem(HUDManager, HUD, HUD)
RegisterSystem(Lighting, LAST, LAST)
RegisterSystem(DebugManager, Debug, Debug)
RegisterSystem(TimerManager, FIRST, FIRST)
RegisterSystem(Camera, FIRST, Camera)
RegisterSystem(Render, Render, Render)
RegisterSystem(ActionManager, Action, Action)
RegisterSystem(InputManager, Input, Input)
RegisterSystem(WindowManager, Window, Window)
RegisterSystem(UniformBuffer, LAST, LAST)
RegisterSystem(DragAndDrop, LAST, LAST)

#pragma endregion 

#pragma region Components
//Register
RegisterComponent(AnimationComponentManager, Animation)
RegisterComponent(SpineAnimationComponentManager, LAST)
RegisterComponent(SpineSkeletonComponentManager, SpineSkeleton)
RegisterComponent(BehaviorComponentManager, Behavior)
RegisterComponent(PhysicsComponentManager, Physics)
RegisterComponent(ColliderComponentManager, Collider)

#pragma endregion 