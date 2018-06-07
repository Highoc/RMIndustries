#include "Entity\Player.hpp"

Player::Player(float x, float y, const sf::Sprite& sprite) : Entity(x, y, sprite)
{}

void Player::keyboard(const sf::Event& event) 
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			vy_ -= 0.1;
			break;
		case sf::Keyboard::Down:
			vy_ += 0.1;
			break;
		case sf::Keyboard::Left:
			vx_ -= 0.1;
			break;
		case sf::Keyboard::Right:
			vx_ += 0.1;
			break;
		}
	}
}




