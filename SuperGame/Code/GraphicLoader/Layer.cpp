#include <GraphicLoader\Layer.hpp>

void Layer::addTile(sf::Sprite tile)
{
	tiles.push_back(std::move(tile));
}

const std::vector<sf::Sprite>& Layer::getTiles()
{
	return tiles;
}