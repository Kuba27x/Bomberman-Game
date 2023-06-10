#include "stdafx.h"
#include "Player.h"

//Init functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

//Con/des
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();
	setPosition(x, y);
	createHitboxComponent(sprite, 0.f, 0.f, 130.f, 170.f);
	createMovementComponent(300.f, 15.f, 5.f);
	createAnimationComponent(texture_sheet);
	animationComponent->addAnimation("IDLE", 11.f, 0, 0, 2, 0, 130, 170);
	animationComponent->addAnimation("WALK_LEFT", 9.f, 0, 1, 2, 1, 120, 170);
	animationComponent->addAnimation("WALK_RIGHT", 9.f, 0, 2, 2, 2, 120, 170);
	animationComponent->addAnimation("WALK_UP", 9.f, 0, 3, 1, 3, 130, 170);
	animationComponent->addAnimation("WALK_DOWN", 9.f, 0, 4, 1, 4, 130, 170);
}

Player::~Player()
{

}

//Functions
void Player::update(const float& dt)
{
	
	movementComponent->update(dt);

	if(movementComponent->getState(IDLE))
		animationComponent->play("IDLE", dt);
	else if(movementComponent->getState(MOVING_LEFT))
		animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	else if (movementComponent->getState(MOVING_RIGHT))
		animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	else if (movementComponent->getState(MOVING_UP))
		animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
	else if (movementComponent->getState(MOVING_DOWN))
		animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());

	hitboxComponent->update();

}
