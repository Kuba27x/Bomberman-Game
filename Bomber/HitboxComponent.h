#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	sf::RectangleShape hitbox;
	sf::Sprite& sprite;
	float offsetX, offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);
	sf::FloatRect getGlobalBounds() const;
	void update();
	void render(sf::RenderTarget& target);
};
#endif