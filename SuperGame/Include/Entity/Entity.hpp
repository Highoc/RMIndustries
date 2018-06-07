#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <../Animation.hpp>
extern sf::RenderWindow window;

class Entity
{
public:
	Entity(float x, float y, const sf::Texture& texture);
	Entity(float x, float y, const sf::Sprite& sprite);
	Entity(float x, float y, float vx, float vy, const sf::Sprite& sprite);

	
	int getWidth();
	int getHeight();

	virtual void draw();
	void move(float time);
	void logic(const sf::Event& event);
	virtual void keyboard(const sf::Event& event, float time) {};
	

protected:
	float x_, y_;
	float vx_, vy_;
	AnimationManager anim;
	sf::Sprite sprite_;
};