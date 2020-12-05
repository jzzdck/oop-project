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
		int m_hue, m_sat, m_val;
	public:
		HSV() : m_hue(0), m_sat(0), m_val(0) {}
		HSV(const sf::Color &rgb);
		HSV(int hue, int sat, int value);
		HSV MakeHSV(const sf::Color &rgb);
		sf::Color MakeRGB();
		
		int GetHue() { return m_hue; }
		int GetSat() { return m_sat; }
		int GetVal() { return m_val; }
		
		void SetHue(int hue);
		void SetSat(int sat);
		void SetVal(int val);
	};
}

#endif

