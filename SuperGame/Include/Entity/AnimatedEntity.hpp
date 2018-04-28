#include "Entity\Entity.hpp"

#include "SFML\Graphics.hpp"

#include <vector>

class AnimatedEntity : protected Entity
{
public:

private:
	size_t n;
	std::vector<sf::Sprite> sprites;
};
