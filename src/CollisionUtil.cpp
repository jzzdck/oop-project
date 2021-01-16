#include "CollisionUtil.h"
#include <limits>
#include <cmath>

namespace utils {
	sf::Rect<float> minkowskiDifference(const Box &b1, const Box &b2) {
		return {
			b1.globals.left - (b2.globals.left + b2.globals.width),
			b1.globals.top - (b2.globals.top + b2.globals.height),
			b1.globals.width + b2.globals.width,
			b1.globals.height + b2.globals.height
		};
	}
	
	bool minkowskiCollision(const sf::Rect<float> &md) {
		// magically, if (0,0) is part of md, b1 and b2 are colliding 
		return (md.left <= 0 && (md.left + md.width) >= 0 &&
				md.top  <= 0 && (md.top + md.height) >= 0);
	}
	
	sf::Vector2f getPenetration(const sf::Rect<float> &md) {
		// assume the closest penetration is to the left
		float min_dist = std::fabs(md.left);
		sf::Vector2f penetration = { md.left - 1, 0 };
		
		// check if there is a shorter penetration
		// md is a rectangle, so there are only 3 checks needed:
		
		// check if the closest penetration is to the right
		if (std::fabs(md.left + md.width) < min_dist) {
			min_dist = std::fabs(md.left + md.width);
			penetration = { md.left + md.width + 1, 0 };
		}
		
		// check if the closest penetration is to the top
		if (std::fabs(md.top) < min_dist) {
			min_dist = std::fabs(md.top);
			penetration = { 0, md.top - 1};
		}
		
		// check if the closest penetration is to the bottom
		if (std::fabs(md.top + md.height) < min_dist) {
			min_dist = std::fabs(md.top + md.height);
			penetration = { 0, md.top + md.height };
		}
		
		return penetration;
	}
}

