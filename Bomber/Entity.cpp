#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	hitboxComponent = NULL;
	movementComponent = NULL; 
	animationComponent = NULL;
}

Entity::Entity()
{
	initVariables();
	
}

Entity::~Entity()
{
	delete hitboxComponent;
	delete movementComponent;
	delete animationComponent;
}

//Comp functions
void Entity::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}


//Functions
void Entity::setPosition(const float x, const float y)
{
	
	sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (movementComponent)
	{
		movementComponent->move(dir_x, dir_y, dt); //Set velocity
	
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if (hitboxComponent)
	{
		hitboxComponent->render(target);
	}
}
