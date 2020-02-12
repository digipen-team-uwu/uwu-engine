![][logo]
# UWU Engine
UWU Engine is a performance oriented, ECS architectured game engine, being developed for the work-in-progress title Project Umbra.

To see all the libraries we used in the UWU Engine, goto [Libraries](docs/LibraryList.md)

- [UWU Engine](#uwu-engine)
  - [Systems](#systems)
  - [Components](#components)

## Systems
All systems are derived from the [base system](docs/Systems/BaseSystem.md).
The following **systems** are currently implemented in UWU Engine:
- [Finite State Machine](docs/Systems/StateMachine.md)
- [Entity Manager](docs/Systems/EntitySys.md)
- [Entity Factory](docs/Systems/EntityFactory.md)
- [Frame Rate Controller](docs/Systems/FrameRateController.md)
- [Render](docs/Systems/Render.md)
- [Random](docs/Systems/Random.md)
- [Sound](docs/Systems/Sound.md)
- [Camera](docs/Systems/Camera.md)
- [Dynamic Camera](docs/Systems/DynamicCamera.md)
- [Debug](docs/Systems/Debug.md)
- [Editor](docs/Systems/Editor.md)
- [Timer](docs/Systems/Timer.md)
- [Input](docs/Systems/Input.md)
- [ActionManager](docs/Systems/ActionManager.md)
- [DragAndDrop](docs/Systems/DragAndDrop.md)
- [Lighting](docs/Systems/Lighting.md)
- [Atlaser](docs/Systems/Atlaser.md)
- [Loader](docs/Systems/Loader.md)

## Components
All components are derived from the [base component](docs/BaseComponent.md).
The following **components** are able to be attached to an entity:
- [Transform](docs/Components/Transform.md)
- [Physics](docs/Components/Physics.md)
- [Animation](docs/Components/Animation.md)
- [Collider](docs/Components/Collider.md)
- [Behavior](docs/Components/Behavior.md)
- [Lighting](docs/Components/Lighting.md)
- [Parent-Child (Hierarchy)](docs/Components/ParentChild.md)
- [Spine Skeleton](docs/Components/SpineSkeleton.md)
- [Spine Animation](docs/Components/SpineAnimation.md)

The following **components** are stateless, meaning they can be attached to multiple entities and do not need to be updated once loaded.
- [Shader](docs/Stateless/Shader.md)
- [Mesh](docs/Stateless/Mesh.md)
- [Texture](docs/Stateless/Texture.md)
- [Spine Data](docs/Stateless/SpineData.md)


[logo]: UWU_engine_logo.png "UWU Engine Logo"
