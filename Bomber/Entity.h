#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	sf::Sprite sprite;
	bool destroyable;
	bool harmful;
	int type; ///1-player, 2-wall, 3-bomb, 4-explosion, 5-boost
	bool killed;
	//Comp functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);

	bool checkEntityCollision(Entity& entity);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

	HitboxComponent* getHitboxComponent() const;
	sf::FloatRect getGlobalBounds() const;
};

#endif // !ENTITY_H