#ifndef BOMB_H
#define BOMB_H
#include "stdafx.h"
#include "Entity.h"
#include "Player.h"

class Bomb : public Entity
{
private:
	//Variables

	//Init functions
	void initVariables();
	void initComponents();

public:
	Bomb(float x, float y, float hitbox_width, float hitbox_height, sf::Texture& texture_sheet, Player* owner);
	virtual ~Bomb();

	//Variables
	Player* bombOwner;
	int freePass;
	int safe;
	int lifeTime;
	bool isIncrementingOwner;

	//Functions
	virtual void update(const float& dt, const float windowWidth, const float windowHeight);
};


class Explosion : public Bomb
{
public:
	Explosion(float x, float y, float width, float height, sf::Texture& texture_sheet, Player* owner, int lifeTime, int orientation);
	void update(const float& dt, const float windowWidth, const float windowHeight) override;
};



#endif