#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.f);
	hitbox.setOutlineColor(sf::Color::Green); //Set to transparent to make it invisible
}

HitboxComponent::~HitboxComponent()
{

}

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}
