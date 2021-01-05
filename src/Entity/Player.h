#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "../Controls.h"
#include "Item/Item.h"
#include "Item/Weapon/Weapon.h"

/// @brief The Player class relates players' input to the game.
class Player : public Entity {
public:
	/// @brief Update the player in relation to input.
	void Update() override; // every component would get updated
	
	/// @brief Draw the player in the current window.
	/// @param win Where the player will be drawed.
	void Draw(sf::RenderWindow &win) override; // graphics component's job
	
	/// @brief In case of collision, apply a response vector to the player.
	/// @param vec A projection vector made in World, recibed from Match.
	void ApplyResponse(const sf::Vector2f &vec) override;
	
	/// @brief Get the player's current jump speed.
	int GetJumpSpeed() const { return m_jumpspeed; }
	/// @brief Get the player's index.
	int GetIndex() const { return m_index; }
	
	void UnassignObject(Item* if_item);
	void UnassignObject(Weapon* if_weapon);
	
	void AssignObject(Item* new_item);
	void AssignObject(Weapon* new_weapon);
	
	/// @brief Checks if the player has pressed the 'grab' key.
	bool PressedGrab(Item* if_item);
	bool PressedGrab(Weapon* if_weapon);
	
	/// @brief Construct a player in an initial position, and give it an index.
	/// @param pos Initial player position.
	/// @param player_index Index given to the player. 
	Player(sf::Vector2f pos, int player_index);
	bool can_grab, set_grab;
private:
	int m_index;
	
	Controls m_input;
	void LoadKeys();
	
	int m_jumpcount, m_jumpspeed; 
	bool is_jumping;
	
	Item *m_item;
	Weapon *m_weapon; 
	
	int current_sprite;
	sf::Sprite ms_belly;
	void LoadBelly();
	std::vector<sf::Texture> mt_belly;
};

#endif

