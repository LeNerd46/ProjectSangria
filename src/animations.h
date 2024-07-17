#pragma once
#include <graphx.h>

#define MAX_FRAMES 5
#define MAX_ANIMATED_OBJECTS 1

struct Animation
{
	gfx_rletsprite_t* frames[MAX_FRAMES];
	int frameDuration;
	unsigned char totalFrames;

	Animation() {}

	Animation(gfx_rletsprite_t* framesReference[], int frameDuration, unsigned char totalFrames) : frames(), frameDuration(frameDuration), totalFrames(totalFrames)
	{
		for (int i = 0; i < totalFrames; i++)
		{
			frames[i] = framesReference[i];
		}
	}
};

class AnimationManager
{
public:
	AnimationManager() : nextObjectId(0) {}

	int createAnimation(Animation* animation);
	void setAnimation(unsigned char objectId, Animation* animation);
	void update(int deltaTime);

	gfx_rletsprite_t* getCurrentFrame(unsigned char objectId) const;

	~AnimationManager()
	{
		for(int i = 0; i < MAX_ANIMATED_OBJECTS; i++)
		{
			delete animationStates[i];
		}
	}

private:
	struct AnimationState
	{
		Animation* animation;
		int currentFrame;
		int elapsedTime;

		AnimationState() : animation(nullptr), currentFrame(0), elapsedTime(0) {}
	};

	AnimationState* animationStates[MAX_ANIMATED_OBJECTS]{};
	unsigned char nextObjectId;
};