#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

//Functions
void AnimationComponent::addAnimation(const std::string key, float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

void AnimationComponent::play(const std::string key, const float& dt)
{
	if (lastAnimation != animations[key])
	{
		if (lastAnimation == NULL)
			lastAnimation = animations[key];
		else
		{
			lastAnimation->reset();
			lastAnimation = animations[key];
		}
	}

	animations[key]->play(dt);
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max)
{
	if (lastAnimation != animations[key])
	{
		if (lastAnimation == NULL)
			lastAnimation = animations[key];
		else
		{
			lastAnimation->reset();
			lastAnimation = animations[key];
		}
	}

	animations[key]->play(dt, abs(modifier / modifier_max));
}