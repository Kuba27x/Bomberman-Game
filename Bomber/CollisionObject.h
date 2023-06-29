#ifndef COLLISIONOBJECT_H
#define COLLISIONOBJECT_H

#include "Entity.h"
#include "SFML/Graphics.hpp"

struct CollisionObject
{
    sf::FloatRect rectangle;
    Entity* entity = nullptr;
};

#endif