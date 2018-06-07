#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class Object
{
public:
	Object(std::string name, std::string type, sf::Sprite sprite);
	void addProperty(std::string propertyName, std::string propertyValue);

	const sf::Vector2f& getPosition();
	const sf::Sprite getSprite();
private:
	std::string name;
	std::string type;
	
	std::map<std::string, std::string> properties;
	sf::Sprite sprite;
};