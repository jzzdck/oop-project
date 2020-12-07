#ifndef MATCH_H
#define MATCH_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Menu.h"
#include "Scene.h"
#include "Player.h"
#include "World.h"
#include <vector>

/** @brief The Match class handles the connection between the elements of the game; 
		World, Player, Weapons, etc
**/
class Match : public Escena {
public:
	/// @brief Update the game's state in relation to the current Match events
	/// This is where most of the game logic (the relationship between entities) occurs.
	/// @param g The Match returns to the game some information, for example, the current scene must be changed.
	void Update(Game & g);
	
	/// @brief Draw the Match's elements in the window
	/// @param win The window in where to draw.
	void Draw(sf::RenderWindow & win);
	
	/// @brief Construct the match
	/// @param width The Match class doesn't use this parameter, it is passed down to World
	/// @param height The Match class doesn't use this parameter, it is passed down to World
	Match(float width, float height);
	~Match();
private:
	std::vector<Player> m_players;
	World m_world;
};

#endif

