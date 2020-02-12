# Spine Animation

- [Spine Animation](#spine-animation)
  - [Load a spine skeleton data](#load-a-spine-skeleton-data)
  - [Create a new spine animation component](#create-a-new-spine-animation-component)
  - [Get a spine animation component](#get-a-spine-animation-component)
  - [What to do with a spine animation](#what-to-do-with-a-spine-animation)
    - [Update the animation](#update-the-animation)
    - [Change currently playing animation](#change-currently-playing-animation)
    - [Pause and start playing the animation](#pause-and-start-playing-the-animation)
    - [Get Raw animation](#get-raw-animation)

This component is part of the [UWU Engine](../../README.md).

This is a full implementation of spine c runtime.

A spine animation component stores all the data about the current animation state and animation sequence data.  
It can't be used without a corresponding [spine skeleton](SpineSkeleton.md).

To use this component, include
```cpp
#include "SpineAnimationComponentManager.h"
```

## Load a spine skeleton data
To load a skeleton, you need a `spine atlas` file for texture atlas data and a `spine json` skeleton data. Go to [Spine Data Manager](../Stateless/SpineData.md) to learn more about how to load a spine skeleton

## Create a new spine animation component
To create and attach a new spine animation component, call this function
```cpp
SpineAnimationComponentManager::SetAnimation(EntityID ID, SpineData& spineData);
SpineAnimationComponentManager::SetAnimation(EntityID ID, const char* name);
```
You can either call this function by providing a [spine data](../Stateless/SpineData.md) or provide the name of spine data that's already being loaded in the engine.

## Get a spine animation component
Get a spine animation component of an [entity](../Systems/EntitySys.md) by calling this function
```cpp
SpineAnimation& animation = SpineAnimationComponentManager::GetAnimation(EntityID);
```

## What to do with a spine animation

### Update the animation
Update the animation by calling this function
```cpp
animation.UpdateAnimation(float dt);
```
You can provide any time step you want to this function to forward the animation.

### Change currently playing animation
Change the currently playing animation by calling this function
```cpp
animation.ChangeAnimation(const char* animationName, bool isLooping);
```
The animation name have to be an existing animation name of the skeleton this animation is attached to or the whole engine will crash.  
`TODO:: Fix this after logging system is in place`  
You can choose to let this animation loop or not by providing the `isLooping` boolean.

### Pause and start playing the animation
You can pause the animation by calling
```cpp
animation.StopPlaying();
```
And start playing the animation by calling
```cpp
animation.StartPlaying();
```
You can also check if the animation is currently playing by calling
```cpp
bool isPlaying = animation.IsPlaying();
```

### Get Raw animation
There's a lot you can do with the raw spine animation instance, you can get that with
```cpp
spAnimationState* spAnimation = animation.GetAnimationState();
```
To see what you can do with raw spine animation instance, check the [official spine api](http://esotericsoftware.com/spine-api-reference).
