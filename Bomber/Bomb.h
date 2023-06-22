#ifndef BOMB_H
#define BOMB_H
#include "Entity.h"

class Bomb : public Entity
{
private:
	//Variables

	//Init functions
	void initVariables();
	void initComponents();

public:
	Bomb(float x, float y, sf::Texture& texture_sheet);
	virtual ~Bomb();
	Bomb();

	virtual void update(const float& dt);
};
#endif