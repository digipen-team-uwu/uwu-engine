/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineDataMod.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Spine stateless data manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Modules/SpineDataMod.h>

namespace UWUEngine
{

SpineData::SpineData(const char* atlasPath, const char* jsonPath, float scaleOffset) :
	scaleOffset(scaleOffset), atlasPath_(atlasPath), jsonPath_(jsonPath), atlas_(), skeletonData_(), animationStateData_()
{
	LoadModel();
}

spSkeletonData& SpineData::GetSkeletonData()
{
	return *skeletonData_;
}

const spSkeletonData& SpineData::GetSkeletonData() const
{
	return *skeletonData_;
}

spAnimationStateData& SpineData::GetAnimationStateData()
{
	return *animationStateData_;
}

const spAnimationStateData& SpineData::GetAnimationStateData() const
{
	return *animationStateData_;
}

float SpineData::GetScaleOffset() const
{
	return scaleOffset;
}

void SpineData::LoadModel()
{
	atlas_ = spAtlas_createFromFile(atlasPath_, nullptr);
	spSkeletonJson* json = spSkeletonJson_create(atlas_);
	json->scale = 2;
	skeletonData_ = spSkeletonJson_readSkeletonDataFile(json, jsonPath_);
	animationStateData_ = spAnimationStateData_create(skeletonData_);
	animationStateData_->defaultMix = 0.5;
	if (!skeletonData_)
	{
		printf("%s\n", json->error);
		spSkeletonJson_dispose(json);
		exit(0);
	}
	spSkeletonJson_dispose(json);
}

SpineDataMod::SpineDataMod(ISpace* p) : System(p) {}

void SpineDataMod::LoadData(const char* name, const char* atlasPath, const char* jsonPath, float scaleOffset)
{
	//If the key can't be found in the container
	if (DataContainer.find(name) == DataContainer.end())
	{
		//Insert element
		DataContainer.insert_or_assign(name, SpineData(atlasPath, jsonPath, scaleOffset));
	}
}

void SpineDataMod::LoadData(const char* name, SpineData& data)
{
	DataContainer.insert_or_assign(name, data);
}

SpineData& SpineDataMod::GetData(const char* dataName)
{
	return DataContainer.find(dataName)->second;
}

}