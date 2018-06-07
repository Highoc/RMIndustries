#include "Engine\Engine.hpp"
#include "..\Animation.hpp"

void Engine::run()
{
	GraphicLoader::setFilepathToResourses("C:/Users/haker/Desktop/game/RMIndustries/SuperGame/Resourses/");
	GraphicLoader::loadMapFromXMLFile("Map/test_map_1.tmx");
	
	sf::Sprite sprite;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	AnimationManager anim;
	
	


	playerTexture.loadFromFile("C:/Users/haker/Desktop/game/RMIndustries/SuperGame/Resourses/Animation/go.png");
	playerSprite.setTexture(playerTexture);
	anim.loadFromXML(GraphicLoader::getFilePathToResourses() + "Animation/animationPlayer.xml", playerTexture);

	for (auto& now : GraphicLoader::getLayer(0).getTiles())
	{
		add(new Entity(now.getPosition().x, now.getPosition().y, now));
	}

	for (auto& now : GraphicLoader::getObjects())
	{
		add(new Entity(now.getPosition().x, now.getPosition().y, now.getSprite()));
	}

	Player* player = new Player(0,0,playerSprite);
	add((Entity*) player);
	Clock clock;

	while (window.isOpen())
	{

		sf::Event event;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 100;

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
			entity->draw();
			if ((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased))
			{
				entity->keyboard(event, time);
			}
			entity->move(time);
		}
		window.display();
	}
}

void Engine::add(Entity* entity)
{
	entities.push_back(entity);
}