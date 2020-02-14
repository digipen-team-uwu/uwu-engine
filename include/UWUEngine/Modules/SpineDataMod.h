/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineDataMod.h
\author     Yi Qian
\date       2019/12/05
\brief      Spine stateless data manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <spine/spine.h>
#include <UWUEngine/System.h>
#include <string>
#include <unordered_map>

namespace UWUEngine
{

class SpineData
{
public:
	//Constructors
	SpineData(const char* atlasPath, const char* jsonPath, float scaleOffset);

	spSkeletonData& GetSkeletonData();
	[[nodiscard]] const spSkeletonData& GetSkeletonData() const;

	spAnimationStateData& GetAnimationStateData();
	[[nodiscard]] const spAnimationStateData& GetAnimationStateData() const;

	[[nodiscard]] float GetScaleOffset() const;

private:
	void LoadModel();

	float scaleOffset;

	const char* atlasPath_;
	const char* jsonPath_;

	spAtlas* atlas_;
	spSkeletonData* skeletonData_;
	spAnimationStateData* animationStateData_;
};

class SpineDataMod : public System
{
public:
	SpineDataMod(ISpace*);
	void LoadData(const char* name, const char* atlasPath, const char* jsonPath, float scaleOffset);
	void LoadData(const char* name, SpineData& data);
	SpineData& GetData(const char* dataName);

private:
	std::unordered_map<std::string, SpineData> DataContainer;
};

}
