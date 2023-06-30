#include "stdafx.h"
#include "Wall.h"

//Init functions
void Wall::initVariables()
{

}

//Con/des
Wall::Wall(float x, float y, sf::Texture& texture_sheet)
{
    initVariables();
    destroyable = true;
    harmful = false;
    type = 2;
    killed = false;
    setPosition(x, y);
    createHitboxComponent(sprite, 0.f, 0.f, 150.f, 200.f);
    createMovementComponent(300.f, 15.f, 5.f);
    createAnimationComponent(texture_sheet);
    animationComponent->addAnimation("IDLE", 11.f, 0, 0, 2, 0, 150, 200);
}

Wall::~Wall()
{
}

//Functions
void Wall::update(const float& dt, const float windowWidth, const float windowHeight)
{
    hitboxComponent->update();
}