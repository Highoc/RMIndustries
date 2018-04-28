#pragma once

#include <vector>

#include "SFML\Graphics.hpp"

class Layer
{
public:
	void addTile(sf::Sprite tile);
	const std::vector<sf::Sprite>& getTiles();

private:
	std::vector<sf::Sprite> tiles;
};
