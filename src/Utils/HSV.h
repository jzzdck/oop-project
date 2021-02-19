#ifndef HSV_H
#define HSV_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace utils {
	/// @brief Utility class for converting SFML's rgb to HSV
	class HSV 
	{
		float m_hue, m_sat, m_val, m_alpha;
	public:
		/// @brief Default HSV set to black.
		HSV() : m_hue(0), m_sat(0), m_val(0), m_alpha(100.f) {}
		///@brief Construct a HSV color out of a RGB one. 
		HSV(const sf::Color &rgb);
		/// @brief Make an HSV Color out of hue, saturation or value.
		HSV(float hue, float sat, float value, float alpha);
		HSV(float hue, float sat, float value);
		
		/// @brief Return the RGB version of the current HSV color.
		sf::Color MakeRGB() const;
		
		/// @brief Set current HSV color's hue.
		void SetHue(float hue);
		/// @brief Set current HSV color's saturation.
		void SetSat(float sat);
		/// @brief Set current HSV color's value.
		void SetVal(float val);
		void SetAlpha(float alpha) { m_alpha = std::min(alpha, 99.f); }
		/// @brief Get current HSV color's hue.
		int GetHue() const { return m_hue; }
		/// @brief Get current HSV color's saturation.
		int GetSat() const { return m_sat; }
		/// @brief Get current HSV color's value.
		int GetVal() const { return m_val; }
		int GetAlpha() const { return m_alpha; }
	};
	
	/// @brief Return the HSV version of a RGB color
	HSV MakeHSV(const sf::Color &rgb);
	
	/// @brief Get an HSV color out of a string.
	/// @param hsv A string of the type "hue saturation value" (in numbers)
	/// @return An HSV color
	HSV getColorHSV(std::string hsv);
}

#endif

