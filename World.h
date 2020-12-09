#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <vector>
#include "Settings.h"
#include "Player.h"

class Player;

/** @brief The World class is the place where the Match occurs **/
class World {
public:
	/// @brief Draw m_platforms on the current window
	void Draw(sf::RenderWindow &win);
	
	/// @brief Check if any of the rectangles that make m_platforms collides with a sprite's entity.
	/// @param entity The sprite to check.
	/// @param index From what index start to check in the m_platforms vector.
	int CollidesWith(const sf::Sprite &entity, int index = 0);
	
	/// @brief Get the response vector to undo a collision.
	/// @param index The index of the m_platforms' rectangle that collides
	/// @param entity The sprite to get the response out of.
	sf::Vector2<double> GetResponse(const sf::Sprite &entity, int index);
	
	/// @brief Get the world's current gravity
	float GetGravity() const { return m_gravity; }
	
	/// @brief Get the index of the player's base platform in m_platforms.
	/// @param which Which of the bases; player one's or player two's.
	/// @return An index, -1 if the current world doesnt have any bases.
	int GetBaseIndex(int which) const { return which ? m_base1 : m_base0; };
	
	/// @brief Construct a World
	/// @param wdt The current window's width
	/// @param hgt The current window's height
	/// @param gravity The world's gravity constant
	/// @param map_name The .conf keyword to create the map.
	World(float wdt, float hgt, float gravity, std::string map_name = "MAIN");
private:
	/// @brief Fill the m_platforms vector with RectangleShapes
	/// @param map_name The .conf keyword to create the map.
	void LoadMap(std::string map_name);
	std::vector<sf::RectangleShape> m_platforms; // el "piso" del mundo
	
	float m_gravity;
	float win_width, win_height;
	std::string m_map;
	int m_base0, m_base1;
	sf::Color m_c;
};

#endif

