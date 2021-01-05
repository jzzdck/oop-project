#ifndef MATCH_H
#define MATCH_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "World.h"
#include "../Scene.h"
#include "../../Game.h"
#include "../../Entity/Item/Item.h"

/** @brief The Match class handles the connection between the elements of the game; 
		World, Player, Weapon, etc.
**/

class Match : public Escena {
public:
	void ProcessEvent(sf::Event& e,Game& g)override;
	
	/// @brief Update the game's state in relation to the current Match events.
	/// This is where most of the game logic (the relationship between entities) occurs.
	/// @param g The Match returns to the game some information, for example, if the current scene must be changed.
	void Update(Game & g);
	
	void UpdateCamera();
	void UpdateOwnership(Player &player, bool pressed_grab);
	
	/// @brief Update one of the players in the Match.
	/// This function helps organize the code; it is better to think how to update one player
	/// and then apply that general function to every player.
	/// "Updating" means responding to the world's events: if the player won, if the player collides with the world, etc. 
	/// @param player The player to update.
	void UpdatePlayer(Player &player);
	
	/// @brief Update one of the items in the Match.
	/// This function helps organize the code; it is better to think how to update one item
	/// and then apply that general function to every item.
	/// "Updating" means responding to the world's events: if the item has a new owner, if the item collides with the world, etc.
	/// @param item The item to update.
	void UpdateItem(Item *item);
	
	/// @brief Draw the Match's elements in the window.
	/// @param win The window where to draw.
	void Draw(sf::RenderWindow & win);
	
	/// @brief Construct the match
	/// @param width Match uses this parameter to set the X position of its elements.
	/// @param height Match uses this parameter to set the Y position of its elements.
	Match(float width, float height);
	/// @brief Items are dynamic memory and should be deleted.
	~Match();
private:
	/* se podria tirar todo en un solo vector de Entity,
		pero se entenderia menos qué es cada cosa y donde está */
	std::vector<Player> m_players;
	std::vector<Item*> m_items;
	World m_world;
	
	sf::View m_view;
};

#endif

