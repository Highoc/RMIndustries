#pragma once
#include <SFML\Graphics.hpp>

extern sf::RenderWindow window;

class Entity
{
public:
	Entity(float x, float y, const sf::Texture& texture);
	Entity(float x, float y, const sf::Sprite& sprite);

	float getWidth();
	float getHeight();

	void draw();
	//void move(float time);
	//void logic();

private:
	float x_, y_;
	//float vx_, vy_;

	sf::Sprite sprite_;
};