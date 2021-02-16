#ifndef GUTILS_H
#define GUTILS_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace utils {
	void flipTexture(float direction, float scale, sf::Sprite &to_turn);
	sf::Rect<float> getRectDim(std::string s);
	std::string rectDimsToString(const sf::Rect<float> &to_convert);
	sf::Vector2f getXY(std::string s);
	std::string getRandomMap();
	std::vector<std::string> getMapnames();
	int wrap(int &to_wrap, int range);
	
	/// @brief Get the center point of a rectangle
	/// @return the x and y coordinates of the center
	sf::Vector2f getCenter(const sf::Rect<float>& of_this);
	
	/// @brief Get an SFML color out of a string.
	/// @param rgb A string of the type "red green blue" (in numbers)
	/// @return An SFML RGB color
	sf::Color getColor(std::string rgb);
	std::string getColorString(sf::Color rgb);
	
	/// @brief Load the player current default color
	/// @return the SFML RGB version of the player's color
	sf::Color loadPlayerColor(int player_index);
	
	/// @brief Get a random float between 0 and 1.
	float randf();
	
	// NOTE: abpos and revpos are percentages of the RenderWindow's size
	sf::Vector2f getFixedPos(sf::RenderWindow * win, const sf::Vector2f & abpos, const sf::Vector2f & revpos);
	
	sf::Vector2f randomPos(const sf::Rect<float> &spawnbox);
}

#endif

