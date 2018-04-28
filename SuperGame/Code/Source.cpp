#include <iostream>
#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"
#include "Entity/Entity.hpp"

sf::RenderWindow window(sf::VideoMode(1200, 600), "Cool game!");

int main()
{
	Engine e;
	e.run();

	system("pause");
	return 0;
}