#include "GraphicLoader\GraphicLoader.hpp"

size_t GraphicLoader::width;
size_t GraphicLoader::height;
size_t GraphicLoader::tileWidth;
size_t GraphicLoader::tileHeight;
std::string GraphicLoader::filepathToResourses;
std::vector<Layer> GraphicLoader::layers;
std::map<size_t, Tileset> GraphicLoader::tilesets;

void GraphicLoader::setFilepathToResourses(const std::string filepath)
{
	filepathToResourses = filepath;
}

bool GraphicLoader::loadMapFromXMLFile(const std::string filename)
{
	TXML::XMLDocument mapXMLDocument;
	if (int errorID = mapXMLDocument.LoadFile((filepathToResourses + filename).c_str()))
	{
		std::cout << 
			"Loading map from \"" << filepathToResourses + filename << "\" failed. "
			"Error code = " << errorID << std::endl;
		return false;
	}

	TXML::XMLElement* mapElement = mapXMLDocument.FirstChildElement("map");
	if (!mapElement)
	{
		std::cout << "Missing tag <map ... > ... </map>";
		return false;
	}

	GraphicLoader::width = mapElement->IntAttribute("width");
	height		= mapElement->IntAttribute("height");
	tileWidth	= mapElement->IntAttribute("tilewidth");
	tileHeight	= mapElement->IntAttribute("tileheight");

	if (mapElement->Attribute("orientation") != std::string("isometric"))
	{
		std::cout << "Map orientation must be isometric" << std::endl;
		return false;
	}

	if (!loadMapTileset(mapElement))
	{
		std::cout << "Loading tilesets failed." << std::endl;
		return false;
	}

	if (!loadMapLayers(mapElement))
	{
		std::cout << "Loading layers failed." << std::endl;
		return false;
	}

	/*if (!loadMapObjects(mapElement))
	{
		std::cout << "Loading objects failed." << std::endl;
		return false;
	}*/

	return true;
}

bool GraphicLoader::loadMapTileset(const TXML::XMLElement* map)
{
	const TXML::XMLElement* tilesetElement = map->FirstChildElement("tileset");
	while (tilesetElement)
	{
		size_t firstGID = tilesetElement->IntAttribute("firstgid");

		const TXML::XMLElement* imageElement = tilesetElement->FirstChildElement("image");
		std::string imagepath = imageElement->Attribute("source");

		sf::Image image;
		if (!image.loadFromFile(filepathToResourses + imagepath))
		{
			std::cout <<
				"Failed to load tileset_image from" << filepathToResourses + imagepath << ". "
				"GID = " << firstGID << std::endl;
			return false;
		}

		sf::Texture tilesetTexture;
		tilesetTexture.loadFromImage(image);

		Tileset tileset(
			firstGID, tilesetElement->Attribute("name"), 
			tilesetElement->IntAttribute("tilewidth"), tilesetElement->IntAttribute("tileheight"),
			tilesetElement->IntAttribute("tilecount"),
			tilesetTexture	
			);

		tilesets[firstGID] = std::move(tileset);

		tilesetElement = tilesetElement->NextSiblingElement("tileset");
	}
	
	return true;
}

bool GraphicLoader::loadMapLayers(const TXML::XMLElement* map)
{
	const TXML::XMLElement* layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		const TXML::XMLElement *layerDataElement = layerElement->FirstChildElement("data");
		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		std::string data = layerDataElement->GetText();

		size_t width = layerElement->IntAttribute("width");
		size_t height = layerElement->IntAttribute("height");

		std::istringstream is(data);
		std::string s;
		int x = width - 1, y = 0, i = 0;
		while (std::getline(is, s, ','))
		{
			int tileGID = stoi(s);

			sf::Sprite sprite = getSprite(tileGID);
			sprite.setPosition(x * tileWidth/2, 150 + y * tileHeight/2 - sprite.getTextureRect().height + tileHeight);
			layer.addTile(sprite);

			i++;
			x++;
			y++;
			if (i == height)
			{
				x = x - height - 1;
				y = y - height + 2 - 1;
				i = 0;
			}
		}

		layers.push_back(std::move(layer));

		layerElement = layerElement->NextSiblingElement("layer");
	}

	return true;
}


sf::Sprite GraphicLoader::getSprite(size_t id)
{
	sf::Sprite sprite;

	for (const auto& now : tilesets)
	{
		if (now.second.containsID(id))
		{
			sprite.setTexture(now.second.getTexture());
			sprite.setTextureRect(now.second.getTextureRect(id));
			break;
		}
	}

	return sprite;
}

std::vector<Layer>& GraphicLoader::getLayers()
{
	return layers;
}

Layer& GraphicLoader::getLayer(size_t id)
{
	return layers.at(id);
}

/*
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "tinyxml2.h"
/*

class Level
{
public:
bool LoadFromFile(std::string filename);

void Draw(sf::RenderWindow &window);
sf::Vector2i GetTileSize();
std::vector<Layer> layers;
private:
int width, height, tileWidth, tileHeight;
int firstTileID;
sf::Rect<float> drawingBounds;
sf::Texture tilesetImage;
//std::vector<Layer> layers;
};
// Работа с объектами
XMLElement *objectGroupElement;

// Если есть слои объектов
if (map->FirstChildElement("objectgroup") != NULL)
{
	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		// Контейнер <object>
		XMLElement *objectElement;
		objectElement = objectGroupElement->FirstChildElement("object");

		while (objectElement)
		{
			// Получаем все данные - тип, имя, позиция, etc
			std::string objectType;
			if (objectElement->Attribute("type") != NULL)
			{
				objectType = objectElement->Attribute("type");
			}
			std::string objectName;
			if (objectElement->Attribute("name") != NULL)
			{
				objectName = objectElement->Attribute("name");
			}
			int x = atoi(objectElement->Attribute("x"));
			int y = atoi(objectElement->Attribute("y"));

			int width, height;

			sf::Sprite sprite;
			sprite.setTexture(tilesetImage);
			sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
			sprite.setPosition(x, y);

			if (objectElement->Attribute("width") != NULL)
			{
				width = atoi(objectElement->Attribute("width"));
				height = atoi(objectElement->Attribute("height"));
			}
			else
			{
				width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
				height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
				sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
			}

			// Экземпляр объекта
			Object object;
			object.name = objectName;
			object.type = objectType;
			object.sprite = sprite;

			sf::Rect <int> objectRect;
			objectRect.top = y;
			objectRect.left = x;
			objectRect.height = height;
			objectRect.width = width;
			object.rect = objectRect;

			// "Переменные" объекта
			XMLElement *properties;
			properties = objectElement->FirstChildElement("properties");
			if (properties != NULL)
			{
				XMLElement *prop;
				prop = properties->FirstChildElement("property");
				if (prop != NULL)
				{
					while (prop)
					{
						std::string propertyName = prop->Attribute("name");
						std::string propertyValue = prop->Attribute("value");

						object.properties[propertyName] = propertyValue;

						prop = prop->NextSiblingElement("property");
					}
				}
			}

			// Пихаем объект в вектор
			objects.push_back(object);

			objectElement = objectElement->NextSiblingElement("object");
		}
		objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
	}
}
else
{
	std::cout << "No object layers found..." << std::endl;
}

return true;
}*/