/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineAnimationComponentManager.h
\author     Yi Qian
\date       2019/12/05
\brief      Spine animation component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once

#include <UWUEngine/Graphics/SpineAnimation/SpineDataManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <unordered_map>

//Component
class SpineAnimation
{
public:
	//Constructors
	explicit SpineAnimation(SpineData& data);

	//Functions
	void UpdateAnimation(float dt) const;
	void ChangeAnimation(const char* animationName, bool isLooping) const;
	void StartPlaying();
	void StopPlaying();
	bool IsPlaying() const;

	//Getters
	spAnimationState* GetAnimationState() const;
	const spAnimationStateData* GetAnimationStateData() const;
	const spSkeletonData* GetSkeletonData() const;
	
private:
	//Data
	spAnimationState* animationState;
	bool isPlaying{true};
};

//Component Manager
class SpineAnimationComponentManager : public BaseComponent<SpineAnimationComponentManager>
{
public:
	void Update() override;
	void InitObject(EntityID ID) override;
	void ShutdownObject(EntityID ID) override;

	static void SetAnimation(EntityID ID, SpineData& data);
	static void SetAnimation(EntityID ID, const char* dataName);
	static SpineAnimation& GetAnimation(EntityID ID);
	
private:
	static std::unordered_map<EntityID, SpineAnimation> animations;
};
