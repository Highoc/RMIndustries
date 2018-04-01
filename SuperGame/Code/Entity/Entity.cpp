#include <Entity\Entity.hpp>

Entity::Entity(float x, float y, const sf::Texture& texture) :
	x_(x), y_(y), sprite_()
{
	sprite_.setTexture(texture);
}

void Entity::draw()
{
	sprite_.setPosition({ x_, y_ });
	window.draw(sprite_);
}