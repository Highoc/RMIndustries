#include <iostream>
#include <SFML/Graphics.hpp>

#include "Engine/Engine.hpp"
#include "Entity/Entity.hpp"

#define X_WINDOW_SIZE 1500
#define Y_WINDOW_SIZE 900

sf::RenderWindow window(sf::VideoMode(X_WINDOW_SIZE, Y_WINDOW_SIZE), "Cool game!");

int main()
{
	
	Engine e;
	
	e.run();

	system("pause");
	return 0;
}