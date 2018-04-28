#pragma once

#include "SFML\Graphics.hpp"

class Tileset
{
public:
	Tileset();

	Tileset(
		size_t id, std::string name, 
		size_t tileWidth, size_t tileHeight,
		size_t tileCount,
		sf::Texture tilesetImage
	);

	size_t getGID() const;
	bool containsID(size_t id) const;

	const sf::Texture& getTexture() const;
	const sf::IntRect& getTextureRect(size_t id) const;


private:
	size_t gid;
	std::string name;

	size_t tileWidth, tileHeight;
	size_t tileCount;
	size_t rows, columns;

	sf::Texture tilesetTexture;
	std::vector<sf::IntRect> subRects;
};
