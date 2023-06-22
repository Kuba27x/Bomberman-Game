#include "stdafx.h"
#include "Wall.h"

//Init functions
void Wall::initVariables()
{

}

void Wall::initComponents()
{

}

//Con/des
Wall::Wall(float x, float y, sf::Texture& texture_sheet)
{
    initVariables();
    setPosition(x, y);
    createHitboxComponent(sprite, 0.f, 0.f, 130.f, 130.f);
    createMovementComponent(300.f, 15.f, 5.f);
    createAnimationComponent(texture_sheet);
    animationComponent->addAnimation("IDLE", 11.f, 0, 0, 2, 0, 130, 130);
}

Wall::~Wall()
{

}

//Functions
void Wall::update(const float& dt, const float windowWidth, const float windowHeight)
{
    // update movement component before checking borders
    movementComponent->update(dt);

    if (sprite.getPosition().x < 0) setPosition(0, sprite.getPosition().y);
    if (sprite.getPosition().y < 0) setPosition(sprite.getPosition().x, 0);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowWidth)
        setPosition(windowWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
    if (sprite.getPosition().y + sprite.getGlobalBounds().height > windowHeight)
        setPosition(sprite.getPosition().x, windowHeight - sprite.getGlobalBounds().height);

    movementComponent->update(dt);

    if (movementComponent->getState(IDLE))
        animationComponent->play("IDLE", dt);
    else if (movementComponent->getState(MOVING_LEFT))
        animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    else if (movementComponent->getState(MOVING_RIGHT))
        animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    else if (movementComponent->getState(MOVING_UP))
        animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
    else if (movementComponent->getState(MOVING_DOWN))
        animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());

    hitboxComponent->update();
}

sf::FloatRect Wall::getGlobalBounds() const
{
    return hitboxComponent->getGlobalBounds();
}

HitboxComponent* Wall::getHitboxComponent() const
{
    return hitboxComponent;
}