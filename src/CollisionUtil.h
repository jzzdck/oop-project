#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace utils {
	struct Box {
		sf::Rect<float> globals;
		sf::Vector2f vel;
	};
	
	float sweptCollision(Box b1, Box b2, sf::Vector2f &normal);
//	float getRemainingTime();
//	void pushResponse();
//	void deflectResponse();
}

#endif
