#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace utils {
	struct Box {
		sf::Rect<float> globals;
		sf::Vector2f vel;
	};
	
	sf::Rect<float> minkowskiDifference(const Box &b1, const Box &b2);
	bool minkowskiCollision(const sf::Rect<float> &md);
	sf::Vector2f getPenetration(const sf::Rect<float> &md);
}

#endif
