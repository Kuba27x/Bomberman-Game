#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "CollisionObject.h"

class Player : public Entity
{
private:
    //Variables
    sf::RenderWindow* window;
    sf::Event event;
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text;

    //Init functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet, std::vector<CollisionObject>* collisionObjects);
    virtual ~Player();

    int avaibleBombs;
    std::vector<CollisionObject>* collisionObjects;

    //Functions
    void update(const float& dt, const float windowWidth, const float windowHeight);
    bool checkCollisionWithObject(const CollisionObject& object);
    void renderText(sf::RenderTarget& target);
    void renderBg(sf::RenderTarget* target);
};

#endif