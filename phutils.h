#ifndef PHUTILS_H
#define PHUTILS_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace utils {
	// obtener el centro de una figura rectangular
	sf::Vector2f getCenter(const sf::Rect<float> &of_this);
	// obtener el color de una string del tipo "r g b"
	sf::Color getColor(std::string rgb);
	
	class HSV {
		double hue, sat, value;
	public:
		HSV() : hue(0), sat(0), value(0) {}
		HSV(const sf::Color &rgb);
		HSV MakeHSV(const sf::Color &rgb);
		sf::Color MakeRGB();
		
		double &GetHue() { return hue; }
		double &GetSat() { return sat; }
		double &GetVal() { return value; }
	};
}

#endif

