#include "GraphicLoader\GraphicLoader.hpp"

#define X_WINDOW_SIZE 1500
#define Y_WINDOW_SIZE 900

size_t GraphicLoader::width;
size_t GraphicLoader::height;
size_t GraphicLoader::tileWidth;
size_t GraphicLoader::tileHeight;
std::string GraphicLoader::filepathToResourses;
std::vector<Layer> GraphicLoader::layers;
std::vector<Object> GraphicLoader::objects;
std::map<size_t, Tileset> GraphicLoader::tilesets;

const float GraphicLoader::X_ISOMETRIC = X_WINDOW_SIZE/2;
const float GraphicLoader::Y_ISOMETRIC = 0;

const float GraphicLoader::X_ORTOGONAL = 0;
const float GraphicLoader::Y_ORTOGONAL = 0;

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

	if (!loadMapObjects(mapElement))
	{
		std::cout << "Loading objects failed." << std::endl;
		return false;
	}

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

		int x = 0, y = 0;
		while (std::getline(is, s, ','))
		{
			int tileGID = stoi(s);

			sf::Sprite sprite = getSprite(tileGID);

			//sprite.getTextureRect().height + tileHeight
			sprite.setPosition(X_ISOMETRIC - tileWidth/2 + (x - y)*((float) tileWidth)/2, Y_ISOMETRIC + (x + y)*((float) tileHeight)/2);
			layer.addTile(sprite);

			if (!(++x % width))
			{
				x = 0;
				y++;
			}
		}

		layers.push_back(std::move(layer));

		layerElement = layerElement->NextSiblingElement("layer");
	}

	return true;
}


const float SIN_A = 75 / 167.71;
const float COS_A = 150 / 167.71;

bool GraphicLoader::loadMapObjects(const TXML::XMLElement* map)
{
	const TXML::XMLElement* objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		const TXML::XMLElement* objectElement = objectGroupElement->FirstChildElement("object");
		while (objectElement)
		{
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

			float x = objectElement->FloatAttribute("x");
			float y = objectElement->FloatAttribute("y");

			std::cout << objectName << " " << x << " " << y << std::endl;

			sf::Sprite sprite;
			int width, height;
			if (objectElement->Attribute("width") != NULL)
			{
				width = atoi(objectElement->Attribute("width"));
				height = atoi(objectElement->Attribute("height"));
			}

			if (objectElement->Attribute("gid") != NULL)
			{
				int gid = objectElement->IntAttribute("gid");
				sprite = getSprite(gid);
			}

			sprite.setPosition(X_ISOMETRIC + (x - y) - tileWidth/2, Y_ISOMETRIC + (x + y)/2 - tileHeight);
			Object object(objectName, objectType, sprite);
			
			const TXML::XMLElement* properties = objectElement->FirstChildElement("properties");
			if (properties != NULL)
			{
				const TXML::XMLElement* property = properties->FirstChildElement("property");
				while (property)
				{
					std::string propertyName = property->Attribute("name");
					std::string propertyValue = property->Attribute("value");
					object.addProperty(propertyName, propertyValue);

					property = property->NextSiblingElement("property");
				}
			}
			objects.push_back(object);

			objectElement = objectElement->NextSiblingElement("object");
		}

		objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
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

std::vector<Object>& GraphicLoader::getObjects()
{
	return objects;
}

Layer& GraphicLoader::getLayer(size_t id)
{
	return layers.at(id);
}