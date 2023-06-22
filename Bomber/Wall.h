#ifndef WALL_H
#define WALL_H
#include "stdafx.h"
#include "Entity.h"

class Wall : public Entity
{
private:
	//Variables

	//Init functions
	void initVariables();
	void initComponents();

public:
	Wall(float x, float y, sf::Texture& texture_sheet);
	virtual ~Wall();

	//Functions
	void update(const float& dt, const float windowWidth, const float windowHeight);
	sf::FloatRect getGlobalBounds() const;
	HitboxComponent* getHitboxComponent() const;
};

#endif