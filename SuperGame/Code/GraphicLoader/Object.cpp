#include "GraphicLoader\Object.hpp"

Object::Object(std::string name, std::string type, sf::Sprite sprite) :
	name(name), type(type), properties(), sprite(sprite)
{}

void Object::addProperty(std::string propertyName, std::string propertyValue)
{
	properties[propertyName] = propertyValue;
}

const sf::Vector2f& Object::getPosition()
{
	return sprite.getPosition();
}

const sf::Sprite Object::getSprite()
{
	return sprite;
}