#ifndef PHUTILS_H
#define PHUTILS_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace utils {
	bool wasPressed(bool &prev, bool act);
	
	/// @brief Utility class for converting SFML's rgb to HSV
	class HSV {
		float m_hue, m_sat, m_val;
	public:
		/// @brief Default HSV set to black.
		HSV() : m_hue(0), m_sat(0), m_val(0) {}
		///@brief Construct a HSV color out of a RGB one. 
		HSV(const sf::Color &rgb);
		/// @brief Make an HSV Color out of hue, saturation or value.
		HSV(float hue, float sat, float value);
		
		/// @brief Return the RGB version of the current HSV color.
		sf::Color MakeRGB() const;
		
		/// @brief Set current HSV color's hue.
		void SetHue(float hue);
		/// @brief Set current HSV color's saturation.
		void SetSat(float sat);
		/// @brief Set current HSV color's value.
		void SetVal(float val);
		/// @brief Get current HSV color's hue.
		int GetHue() const { return m_hue; }
		/// @brief Get current HSV color's saturation.
		int GetSat() const { return m_sat; }
		/// @brief Get current HSV color's value.
		int GetVal() const { return m_val; }
	};
	
	/// @brief Return the HSV version of a RGB color
	HSV MakeHSV(const sf::Color &rgb);

	/// @brief Get the center point of a rectangle
	/// @return the x and y coordinates of the center
	sf::Vector2f getCenter(const sf::Rect<float> &of_this);
	
	/// @brief Get an SFML color out of a string.
	/// @param rgb A string of the type "red green blue" (in numbers)
	/// @return An SFML RGB color
	sf::Color getColor(std::string rgb);
	
	/// @brief Get an HSV color out of a string.
	/// @param hsv A string of the type "hue saturation value" (in numbers)
	/// @return An HSV color
	HSV getColorHSV(std::string hsv);
	
	/// @brief Load the player current default color
	/// @return the SFML RGB version of the player's color
	sf::Color loadPlayerColor(int player_index);
	
	/// @brief Get a random float between 0 and 1.
	float randf();
}

#endif

