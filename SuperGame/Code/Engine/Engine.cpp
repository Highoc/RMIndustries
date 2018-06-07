#include "Engine\Engine.hpp"


void Engine::run()
{
	GraphicLoader::setFilepathToResourses("D:/GameDev/RMINdustries/SuperGame/Resourses/Map/");
	GraphicLoader::loadMapFromXMLFile("test_map_2.tmx");
	
	sf::Sprite sprite;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	playerTexture.loadFromFile("D:/GameDev/RMINdustries/SuperGame/Resourses/Map/Tile/tile_blue.png");
	playerSprite.setTexture(playerTexture);
	for (auto& now: GraphicLoader::getLayer(0).getTiles())
	{
		add(new Entity(now.getPosition().x, now.getPosition().y, now));
	}

	for (auto& now : GraphicLoader::getObjects())
	{
		add(new Entity(now.getPosition().x, now.getPosition().y, now.getSprite()));
	}

	Player* player = new Player(0,0,playerSprite);
	add((Entity*) player);

	while (window.isOpen())
	{
		sf::Event event;
		//std::cout << "--TICK--" << std::endl;
		if (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		else
		{
			event = sf::Event();
		}

		window.clear();
		
		for (const auto& entity: entities)
		{
			entity->logic(event);
			entity->move(0);
			entity->draw();
			entity->keyboard(event);
		}
		window.display();
	}
}

void Engine::add(Entity* entity)
{
	entities.push_back(entity);
}