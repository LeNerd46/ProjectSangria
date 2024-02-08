#include "animations.h"

int AnimationManager::createAnimation(Animation* animation)
{
    unsigned char objectId = nextObjectId++;

    animationStates[objectId] = new AnimationState();
    animationStates[objectId]->animation = animation;

    return objectId;
}

void AnimationManager::setAnimation(unsigned char objectId, Animation* animation)
{
	animationStates[objectId]->animation = animation;
    // animationStates[objectId]->currentFrame = 0;
    // animationStates[objectId]->elapsedTime = 0;
}

void AnimationManager::update(int deltaTime)
{
    for (int i = 0; i < MAX_ANIMATED_OBJECTS; i++)
    {
        if (animationStates[i] == nullptr || animationStates[i]->animation == nullptr)
            continue;

        animationStates[i]->elapsedTime += deltaTime;

        if (animationStates[i]->elapsedTime >= animationStates[i]->animation->frameDuration)
        {
            animationStates[i]->elapsedTime -= animationStates[i]->animation->frameDuration;
            animationStates[i]->currentFrame++;

            if (animationStates[i]->currentFrame >= animationStates[i]->animation->totalFrames)
            {
                animationStates[i]->currentFrame = 0;

                // If you want the animation to stop after one loop
                // animationStates[i]->animation = nullptr;
            }
        }
    }
}

gfx_rletsprite_t* AnimationManager::getCurrentFrame(unsigned char objectId) const
{
    const AnimationState* animationState = animationStates[objectId];

    if(animationState != nullptr && animationState->animation != nullptr)
        return animationState->animation->frames[animationState->currentFrame];

    return nullptr;
}
