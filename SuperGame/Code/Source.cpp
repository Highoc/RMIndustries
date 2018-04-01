#include <iostream>
#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"
#include "Entity/Entity.hpp"

sf::RenderWindow window(sf::VideoMode(300, 900), "Cool game!");

int main()
{
	sf::Texture tile1; tile1.loadFromFile("Resourses/Tile/tile1.png");
	sf::Texture tile2; tile2.loadFromFile("Resourses/Tile/tile2.png");
	sf::Texture tile3; tile3.loadFromFile("Resourses/Tile/tile3.png");

	Engine e;
	e.add(new Entity(0, 0, tile1));
	e.add(new Entity(0, 300, tile2));
	e.add(new Entity(0, 600, tile3));
	e.run();

	system("pause");
	return 0;
}