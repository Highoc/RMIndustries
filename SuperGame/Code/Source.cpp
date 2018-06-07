#include <iostream>
#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"
#include "Engine/Level.hpp"
#include "Entity/Entity.hpp"

#define X_WINDOW_SIZE 1500
#define Y_WINDOW_SIZE 900

sf::RenderWindow window(sf::VideoMode(X_WINDOW_SIZE, Y_WINDOW_SIZE), "Cool game!");

int main()
{
	sf::Texture tile1; tile1.loadFromFile("Resourses/Tile/tile1.png");
	sf::Texture tile2; tile2.loadFromFile("Resourses/Tile/tile2.png");
	sf::Texture tile3; tile3.loadFromFile("Resourses/Tile/tile3.png");

	Engine e;
	Level level;
	level.LoadFromFile("Resourses/Map/bomsh2.tmx");
	
	for (const auto& object : level.GetAllObjects())
	{
		e.add(new Entity(object.rect.left, object.rect.top, object.sprite));
	}
	//e.add(new Entity(0, 0, tile1));
	//e.add(new Entity(0, 300, tile2));
	//e.add(new Entity(0, 600, tile3));

	e.run();
	level.Draw(window);
	system("pause");
	return 0;
}