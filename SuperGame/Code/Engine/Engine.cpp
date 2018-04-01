#include "Engine\Engine.hpp"

void Engine::run()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (const auto& entity: entities)
		{
			entity->draw();
		}
		window.display();
	}
}

void Engine::add(Entity* entity)
{
	entities.push_back(entity);
}