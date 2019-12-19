# Spine Data

Spine data is how a spine skeleton and animation data are being loaded in [UWU Engine](../../README.md).  

This is a full implementation of spine c runtime.

To load a spine data, you need to include
```cpp
#include "SpineData.h"
```

## How to load a spine data

This is easy, you just call this

```cpp
SpineDataManager::LoadData(const char * name, const char* atlasPath, const char* jsonPath);
SpineDataManager::LoadData(const char* name, SpineData& data);
```

Provide the `spine json path` and `spine atlas path` and the name of this spine skeleton data, then everything will be good to go.

## Generate skeleton and animation component

Check [spine skeleton](../Components/SpineSkeleton.md) and [spine animation](../Components/SpineAnimation.md) to learn about how to use the spine data to generate skeleton and animation components.
