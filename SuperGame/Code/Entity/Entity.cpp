#include <Entity\Entity.hpp>

Entity::Entity(float x, float y, const sf::Texture& texture) :
	x_(x), y_(y), sprite_()
{
	sprite_.setTexture(texture);
}

Entity::Entity(float x, float y, const sf::Sprite& sprite) :
	x_(x), y_(y), sprite_(sprite) {}

float Entity::getWidth()
{
	return sprite_.getTextureRect().width;
}
float Entity::getHeight()
{
	return sprite_.getTextureRect().height;

}


void Entity::draw()
{
	sprite_.setPosition({ x_, y_ });
	window.draw(sprite_);
}