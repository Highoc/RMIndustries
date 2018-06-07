#include <Entity\Entity.hpp>

Entity::Entity(float x, float y, const sf::Texture& texture) :
	x_(x), y_(y), sprite_()
{
	sprite_.setTexture(texture);
}

Entity::Entity(float x, float y, const sf::Sprite& sprite) :
	Entity(x, y, 0, 0, sprite) {}

Entity::Entity(float x, float y, float vx, float vy, const sf::Sprite& sprite) :
	x_(x), y_(y), vx_(vx), vy_(vy), sprite_(sprite) {}



int Entity::getWidth()
{
	return sprite_.getTextureRect().width;
}
int Entity::getHeight()
{
	return sprite_.getTextureRect().height;
}


void Entity::draw()
{
	
	sprite_.setPosition({ x_, y_ });
	window.draw(sprite_);
}

void Entity::move(float time)
{
	x_ += vx_ * time;
	y_ += vy_ * time;
}

void Entity::logic(const sf::Event& event)
{
}

