#include "GraphicLoader\Tileset.hpp"

Tileset::Tileset() :
	gid(0), name(""),
	tileWidth(0), tileHeight(0),
	tileCount(0),
	columns(0), rows(0),
	tilesetTexture(),
	subRects()
{}

Tileset::Tileset(
	size_t id, std::string name,
	size_t tileWidth, size_t tileHeight,
	size_t tileCount,
	sf::Texture tilesetTexture
) :
	gid(id), name(name),
	tileWidth(tileWidth), tileHeight(tileHeight),
	tileCount(tileCount),
	columns(0), rows(0),
	tilesetTexture(tilesetTexture),
	subRects()
{
	columns = tilesetTexture.getSize().x / tileWidth;
	rows = tilesetTexture.getSize().y / tileHeight;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::IntRect rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}
}

size_t Tileset::getGID() const
{
	return gid;
}

bool Tileset::containsID(size_t id) const
{
	return (gid <= id) && (id < gid + tileCount);
}

const sf::Texture& Tileset::getTexture() const
{
	return tilesetTexture;
}

const sf::IntRect& Tileset::getTextureRect(size_t id) const
{
	return subRects.at(id - gid);
}