#pragma once
#include <SFML\Graphics.hpp>

extern sf::RenderWindow window;

class Entity
{
public:
	Entity(float x, float y, const sf::Texture& texture);
	void draw();

private:
	float x_, y_;
	sf::Sprite sprite_;
};