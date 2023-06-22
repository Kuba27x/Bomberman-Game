#include "stdafx.h"
#include "Bomb.h"

//Init functions
void Bomb::initVariables()
{

}

void Bomb::initComponents()
{

}

Bomb::~Bomb()
{

}

//Con/des
Bomb::Bomb(float x, float y, sf::Texture& texture_sheet)
{
    initVariables();
    setPosition(x, y);
    createHitboxComponent(sprite, 0.f, 0.f, 130.f, 170.f);
    //createMovementComponent(300.f, 15.f, 5.f);
    createAnimationComponent(texture_sheet);
    animationComponent->addAnimation("IDLE", 11.f, 0, 0, 2, 0, 130, 170);
}

//Functions
void Bomb::update(const float& dt)
{

}