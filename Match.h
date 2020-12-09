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
#include "Entity.h"
#include "phutils.h"
#include <vector>

/** @brief The Match class handles the connection between the elements of the game; 
		World, Player, Weapon, etc.
**/
class Match : public Escena {
public:
	/// @brief Update the game's state in relation to the current Match events.
	/// This is where most of the game logic (the relationship between entities) occurs.
	/// @param g The Match returns to the game some information, for example, if the current scene must be changed.
	void Update(Game & g);
	
	/// @brief Draw the Match's elements in the window.
	/// @param win The window where to draw.
	void Draw(sf::RenderWindow & win);
	
	/// @brief Construct the match
	/// @param width Match uses this parameter to set the X position of its elements.
	/// @param height Match uses this parameter to set the Y position of its elements.
	Match(float width, float height);
	~Match();
private:
	/* se podria tirar todo en un solo vector de Entity,
		pero se entenderia menos qu� es cada cosa y donde est� */
	std::vector<Player> m_players;
	std::vector<Item*> m_items;
	World m_world;
};

#endif

