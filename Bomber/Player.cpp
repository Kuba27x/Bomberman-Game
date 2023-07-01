#include "stdafx.h"
#include "Player.h"

//Init functions
void Player::initVariables()
{
    avaibleBombs = 1;
}

void Player::initComponents()
{

}

//Con/des
Player::Player(float x, float y, sf::Texture& texture_sheet, std::vector<CollisionObject>* collisionObjects)
{
    this->collisionObjects = collisionObjects;
    type = 1;
    killed = false;
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
    delete window;
}

//Functions
void Player::update(const float& dt, const float windowWidth, const float windowHeight)
{
    // Update movement component, check borders
    movementComponent->update(dt);

    // Save position
    sf::Vector2f lastPosition = sprite.getPosition();

    // Check borders
    if (sprite.getPosition().x < 0) setPosition(0, sprite.getPosition().y);
    if (sprite.getPosition().y < 0) setPosition(sprite.getPosition().x, 0);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowWidth)
        setPosition(windowWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
    if (sprite.getPosition().y + sprite.getGlobalBounds().height > windowHeight)
        setPosition(sprite.getPosition().x, windowHeight - sprite.getGlobalBounds().height);

    // Check collision
    for (auto it = collisionObjects->begin(); it != collisionObjects->end(); ++it)
    {
        CollisionObject& object = *it;

        if (checkCollisionWithObject(object))
        {
            sf::Vector2f push;
            sf::FloatRect intersection;
            sprite.getGlobalBounds().intersects(object.rectangle, intersection);

            float intersectionWidth = intersection.width;
            float intersectionHeight = intersection.height;

            if (intersectionWidth > intersectionHeight)
            {
                if (sprite.getPosition().y > object.rectangle.top)
                    push.y = intersectionHeight;
                else
                    push.y = -intersectionHeight;
            }
            else
            {
                if (sprite.getPosition().x > object.rectangle.left)
                    push.x = intersectionWidth;
                else
                    push.x = -intersectionWidth;
            }

            sprite.setPosition(lastPosition + push);
            movementComponent->stopVelocity(dt);

            //End game condition
            if (object.entity && object.entity->harmful)
            {
                window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME OVER", sf::Style::Titlebar | sf::Style::Close);
                window->clear();
                background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
                bgTexture.loadFromFile("Resources/Images/Bbackground.png");
                background.setTexture(&bgTexture);
                renderBg(window);
                if (!font.loadFromFile("Fonts/Brant.ttf"))
                {
                    throw("ERROR::MAINMENUSTATE::COULD NOT LOAD THE FONT!!!");
                }
                text.setFont(font);
                text.setPosition(sf::Vector2f(500.f, 400.f));
                text.setCharacterSize(200);
                text.setFillColor(sf::Color::White);
                text.setString(
                    "GAME OVER\nPRESS ESCAPE\nTO QUIT");
                renderText(*window);
                window->display();
                while (true)
                {
                    window->pollEvent(event);
                    if (event.type == sf::Event::Closed)
                    {
                        std::exit(0);
                        break;
                    }
                    else if (event.type == sf::Event::KeyPressed)
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            std::exit(0);
                            break;
                        }
                }
                break;
            }
            break;
        }
    }

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

bool Player::checkCollisionWithObject(const CollisionObject& object)
{
    return hitboxComponent->checkIntersect(object.rectangle);
}

void Player::renderText(sf::RenderTarget& target)
{
    target.draw(this->text);
}

void Player::renderBg(sf::RenderTarget* target)
{
    target->draw(this->background);
}