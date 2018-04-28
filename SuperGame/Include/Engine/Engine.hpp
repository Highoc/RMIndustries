#pragma once

#include <list>

#include "Entity\Entity.hpp"
#include "GraphicLoader\GraphicLoader.hpp"

extern sf::RenderWindow window;

class Engine 
{
public:
	void add(Entity* entity);
	void run();

private:
	std::list<Entity*> entities;
};
