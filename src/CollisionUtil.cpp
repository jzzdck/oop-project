#include "CollisionUtil.h"
#include <limits>

namespace utils {
	float sweptCollision(Box b1, Box b2, sf::Vector2f &normal) {
		sf::Vector2f inv_near, inv_far;
		sf::Vector2f near, far;
		
		if (b1.vel.x > 0.0f) {
			inv_near.x = b2.globals.left - (b1.globals.left + b1.globals.width);
			inv_far.x = (b2.globals.left + b2.globals.width) - b1.globals.left;
		} else {
			inv_near.x = (b2.globals.left + b2.globals.width) - b1.globals.left;
			inv_far.x = b2.globals.left - (b1.globals.left + b1.globals.width);
		}
		
		if (b1.vel.y > 0.0f) {
			inv_near.y = b2.globals.top - (b1.globals.top + b1.globals.height);
			inv_far.y = (b2.globals.top + b2.globals.height) - b1.globals.top;
		} else {
			inv_near.y = (b2.globals.top + b2.globals.height) - b1.globals.top;
			inv_far.y = b2.globals.top - (b1.globals.top + b1.globals.height);
		}
		
		if (b1.vel.x == 0.0f) {
			near.x = -std::numeric_limits<float>::infinity();
			far.x = std::numeric_limits<float>::infinity();
		} else {
			near.x = inv_near.x / b1.vel.x;
			far.x = inv_far.x / b1.vel.x;
		}
		
		if (b1.vel.y == 0.0f) {
			near.y = -std::numeric_limits<float>::infinity();
			far.y = std::numeric_limits<float>::infinity();
		} else {
			near.y = inv_near.y / b1.vel.y;
			far.y = inv_far.y / b1.vel.y;
		}
		
		float entry_time = std::max(near.x, near.y);
		float exit_time = std::min(far.x, far.y);
		
		if (entry_time > exit_time || 
			near.x < 0.0f && near.y < 0.0f ||
			near.x > 1.0f || near.y > 1.0f) 
		{
			normal.x = 0.0f;
			normal.y = 0.0f;
			return 1.0f;
		} 
		else 
		{
			if (near.x > near.y)
				if (inv_near.x < 0.0f) 
					normal.x = 1.0f, normal.y = 0.0f;
				else
					normal.x = -1.0f, normal.y = 0.0f;
			else
				if (inv_near.y < 0.0f)
					normal.x = 0.0f, normal.y = 1.0f;
				else 
					normal.x = 0.0f, normal.y = -1.0f;
			
			return entry_time;
		}
	}
}
