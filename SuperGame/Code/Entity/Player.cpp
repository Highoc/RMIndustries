#include "Entity\Player.hpp"

Player::Player(AnimationManager& a,float x, float y, const sf::Sprite& sprite) : Entity(x, y, sprite)
{
	
	setAnim(a);
	
}

void Player::keyboard(const sf::Event& event, float time) 
	{
		
		if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				vy_ = -0.01;
				vx_ = -0.02;
				anim.set("up");
				break;
			case sf::Keyboard::Down:
				vy_ = 0.01;
				vx_ = 0.02;
				anim.set("down");
				break;
			case sf::Keyboard::Left:
				vx_ = -0.02;
				vy_ = 0.01;
				anim.set("left");
				break;
			case sf::Keyboard::Right:
				vx_ = 0.02;
				vy_ = -0.01;
				anim.set("right");
				break;
			}
		}
		else
		{
/*
switch (event.key.code)
{
case sf::Keyboard::Up:
case sf::Keyboard::Down:
vy_ = 0;
break;
case sf::Keyboard::Left:
case sf::Keyboard::Right:
vx_ = 0;
break;
}
*/
			if ((event.key.code != sf::Keyboard::Up) || (event.key.code != sf::Keyboard::Down))
			{
				vy_ = 0;
			}
			if ((event.key.code != sf::Keyboard::Left) || (event.key.code != sf::Keyboard::Right))
			{
				vx_ = 0;
			}
		}
		
		
	
		anim.tick(time);
}

void Player::setAnim(AnimationManager &a)
{
	anim = a;
	anim.set("down");
	anim.tick(0);
}
void Player::draw()
{
	
	anim.draw(window, x_, y_);
}



