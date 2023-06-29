#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "HitboxComponent.h"

class Player : public Entity
{
private:
    //Variables

    //Init functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    struct CollisionObject 
    {
        sf::FloatRect rectangle;
        Entity* entity = nullptr;
    };

    int avaibleBombs;

    //Functions
    void update(const float& dt, const float windowWidth, const float windowHeight);
    bool checkCollisionWithObject(const CollisionObject& object);
    void addCollisionObject(const sf::FloatRect& object, Entity* entity);
    void removeCollisionObject(Entity* entity);
    std::vector<CollisionObject> collisionObjects;
};

#endif