#include "phutils.h"

namespace utils {
	sf::Vector2f getCenter(const sf::Rect<float> & of_this) {
		float x_center = of_this.left+of_this.width/2;
		float y_center = of_this.top+of_this.height/2;
		return { x_center, y_center };
	}
	
	sf::Color getColor(std::string rgb) {
		int r, g, b;
		std::stringstream ss;
		
		ss << rgb;
		ss >> r >> g >> b;
		
		return sf::Color(r, g, b);
	}
	
	HSV::HSV (const sf::Color & rgb) {
		
	}
	
	HSV HSV::MakeHSV (const sf::Color & rgb) {
		
	}
	
	sf::Color HSV::MakeRGB ( ) {
		
	}
}

