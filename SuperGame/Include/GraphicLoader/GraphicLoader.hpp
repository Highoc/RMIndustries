#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "tinyxml2.h"
#include "GraphicLoader\Tileset.hpp"
#include "GraphicLoader\Layer.hpp"
#include "GraphicLoader\Object.hpp"



extern sf::RenderWindow window;

namespace TXML = tinyxml2;

class GraphicLoader
{
public:
	static void setFilepathToResourses(const std::string filepath);
	static bool loadMapFromXMLFile(const std::string filename);

	static sf::Sprite getSprite(size_t id);
	
	static Layer& getLayer(size_t id);
	static std::vector<Layer>& getLayers();
	static std::vector<Object>& getObjects();

private:
	static bool loadMapTileset(const TXML::XMLElement* map);
	static bool loadMapLayers(const TXML::XMLElement* map);
	static bool loadMapObjects(const TXML::XMLElement* map);

	static std::string filepathToResourses;

	//Расположение вернего углa
	static const float X_ISOMETRIC, Y_ISOMETRIC;
	static const float X_ORTOGONAL, Y_ORTOGONAL;

	//Размеры карты в тайлах, размеры тайлов в px
	static size_t width, height;
	static size_t tileWidth, tileHeight;

	//Набор тайлсетов и слоев
	static std::map<size_t, Tileset> tilesets;
	static std::vector<Layer> layers;
	static std::vector<Object> objects;
};