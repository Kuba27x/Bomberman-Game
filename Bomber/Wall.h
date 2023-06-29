#ifndef WALL_H
#define WALL_H
#include "stdafx.h"
#include "Entity.h"
#include "CollisionObject.h"

class Wall : public Entity
{
private:
	void initVariables();

public:
	Wall(float x, float y, sf::Texture& texture_sheet);
	virtual ~Wall();

	//Functions
	void update(const float& dt, const float windowWidth, const float windowHeight);
};

#endif