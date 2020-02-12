# Spine Skeleton

- [Spine Skeleton](#spine-skeleton)
  - [Load a spine skeleton data](#load-a-spine-skeleton-data)
  - [Create a new spine skeleton component](#create-a-new-spine-skeleton-component)
  - [Get a spine skeleton component](#get-a-spine-skeleton-component)
  - [What to do with a spine skeleton](#what-to-do-with-a-spine-skeleton)
    - [Change skin](#change-skin)
    - [Get Raw skeleton](#get-raw-skeleton)

This component is part of the [UWU Engine](../../README.md).

This is a full implementation of spine c runtime.

Spine skeleton is an renderable instance of [spine data](../Stateless/SpineData.md).

To use this component, include
```cpp
#include "SpineSkeletonComponentManager"
```

## Load a spine skeleton data
To load a skeleton, you need a `spine atlas` file for texture atlas data and a `spine json` skeleton data. Go to [Spine Data Manager](../Stateless/SpineData.md) to learn more about how to load a spine skeleton

## Create a new spine skeleton component
To create and attach a new spine skeleton component, call this function
```cpp
SpineSkeletonComponentManager::SetSkeleton(EntityID ID, SpineData& spineData);
SpineSkeletonComponentManager::SetSkeleton(EntityID ID, const char* name);
```
You can either call this function by providing a [spine data](../Stateless/SpineData.md) or provide the name of spine data that's already being loaded in the engine.

## Get a spine skeleton component
Get a spine skeleton component of an [entity](../Systems/EntitySys.md) by calling this function
```cpp
SpineSkeleton& skeleton = SpineSkeletonComponentManager::GetSkeleton(EntityID);
```

## What to do with a spine skeleton

### Change skin
You can change the skin of the current animation by simply calling.
```cpp
skeleton.ChangeSkin(const char* skinName);
```
The skin name need to be a name that the skeleton has, the whole engine will crash if a non-existing skin name is used with this function.  
`TODO:: Fix this after logging system is in place`

### Get Raw skeleton
There's a lot you can do with the raw spine skeleton instance, you can get that with
```cpp
spSkeleton* spSkeleton = skeleton.GetSkeleton();
```
To see what you can do with raw spine skeleton instance, check the [official spine api](http://esotericsoftware.com/spine-api-reference).
