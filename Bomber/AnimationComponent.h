#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			sprite.setTexture(textureSheet, true);
			sprite.setTextureRect(startRect);

		}

		//Functions
		void play(const float& dt)
		{

			//Update timer
			timer += 50.f * dt;
			if (timer >= animationTimer)
			{
				//Reset timer
				timer = 0.f;

				//Animate
				if (currentRect != endRect)
				{
					currentRect.left += width;
				}
				else
				{
					//Reset
					currentRect.left = startRect.left;
				}

				sprite.setTextureRect(currentRect);
			}
		}

		void play(const float& dt, float mod_percentage)
		{

			//Update timer
			if (mod_percentage < 0.5f)
				mod_percentage = 0.5f;
			timer += mod_percentage * 50.f * dt;
			if (timer >= animationTimer)
			{
				//Reset timer
				timer = 0.f;

				//Animate
				if (currentRect != endRect)
				{
					currentRect.left += width;
				}
				else
				{
					//Reset
					currentRect.left = startRect.left;
				}

				sprite.setTextureRect(currentRect);
			}
		}

		void reset()
		{
			timer = animationTimer;
			currentRect = startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key, float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	void play(const std::string key, const float& dt);
	void play(const std::string key, const float& dt, const float& modifier, const float& modifier_max);
};
#endif
