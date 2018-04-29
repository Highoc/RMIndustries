#pragma once
#include <Entity\Entity.hpp>

class Player: protected Entity
{
public:
	Player(float x, float y, const sf::Sprite& sprite);
	void keyboard(const sf::Event& event);

};

