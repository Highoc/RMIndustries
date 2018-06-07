#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

extern sf::RenderWindow window;

class Entity
{
public:
	Entity(float x, float y, const sf::Texture& texture);
	Entity(float x, float y, const sf::Sprite& sprite);
	Entity(float x, float y, float vx, float vy, const sf::Sprite& sprite);

	int getWidth();
	int getHeight();

	void draw();
	void move(float time);
	void logic(const sf::Event& event);
	virtual void keyboard(const sf::Event& event) {};

protected:
	float x_, y_;
	float vx_, vy_;

	sf::Sprite sprite_;
};