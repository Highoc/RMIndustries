#pragma once
#include <Entity\Entity.hpp>

class Player: protected Entity
{
public:
	Player(AnimationManager &a, float x, float y, const sf::Sprite& sprite);
	void keyboard(const sf::Event& event, float time);
	void setAnim(AnimationManager &a);
	void draw();
};

