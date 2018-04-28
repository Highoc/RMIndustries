#include "Engine\Engine.hpp"


void Engine::run()
{
	GraphicLoader::setFilepathToResourses("D:/GameDev/RMINdustries/SuperGame/Resourses/Map/");
	GraphicLoader::loadMapFromXMLFile("test_map_1.tmx");
	
	sf::Sprite sprite;
	
	for (auto& now : GraphicLoader::getLayer(0).getTiles())
	{
		add(new Entity(now.getPosition().x, now.getPosition().y, now));
	}



	add(new Entity(0, 0, ));

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
		}
		window.display();
	}
}

void Engine::add(Entity* entity)
{
	entities.push_back(entity);
}