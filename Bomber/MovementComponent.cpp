#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
	maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}


const float& MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

//Functions
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0.f)
			return true;
		break;

	case MOVING:
		if (velocity.x != 0.f || velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:
		if (velocity.x > 0.f)
			return true;
		break;

	case MOVING_UP:
		if (velocity.y < 0.f)
			return true;
		break;

	case MOVING_DOWN:
		if (velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{

	// Store direction of movement
	this->lastMoveDir = sf::Vector2f(dir_x, dir_y);

	//Acceleration
	this->velocity.x += acceleration * dir_x;

	this->velocity.y += acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (velocity.x > 0.f) //right
	{
		//Max velocity check x pos
		if (velocity.x > maxVelocity)
			velocity.x = maxVelocity;

		//Deceleration x pos
		velocity.x -= deceleration;
		if (velocity.x < 0.f)
			velocity.x = 0.f;
	}
	else if (velocity.x < 0.f)
	{
		//Max velocity check x neg
		if (velocity.x < -maxVelocity)
			velocity.x = -maxVelocity;

		//Deceleration x neg
		velocity.x += deceleration;
		if (velocity.x > 0.f)
			velocity.x = 0.f;
	}
	//Deceleration
	if (velocity.y > 0.f) //right
	{
		//Max velocity check y pos
		if (velocity.y > maxVelocity)
			velocity.y = maxVelocity;

		//Deceleration y pos
		velocity.y -= deceleration;
		if (velocity.y < 0.f)
			velocity.y = 0.f;
	}
	else if (velocity.y < 0.f)
	{
		//Max velocity check y neg
		if (velocity.y < -maxVelocity)
			velocity.y = -maxVelocity;

		//Deceleration y neg
		velocity.y += deceleration;
		if (velocity.y > 0.f)
			velocity.y = 0.f;
	}

	//Actual move
	sprite.move(velocity * dt); //Use velocity
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}