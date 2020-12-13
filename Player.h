#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "Controls.h"
#include "Weapon.h"
#include "Revolver.h"
#include "Item.h"

class Game;

/// @brief The Player class relates players' input to the game.
class Player : public Entity {
public:
	/// @brief Update the player in relation to input.
	void Update() override;
	
	/// @brief Draw the player in the current window.
	/// @param win Where the player will be drawed.
	void Draw(sf::RenderWindow &win) override;
	
	/// @brief Apply a constant negative force to the player.
	void ApplyGravity(float gravity);
	
	/// @brief In case of collision, apply a response vector to the player.
	/// @param vec A projection vector made in World, recibed from Match.
	void ApplyResponse(const sf::Vector2<double> &vec) override;
	
	/// @brief Get the player's current jump speed.
	int GetJumpSpeed() const { return m_jumpspeed; }
	/// @brief Get the player's index.
	int GetIndex() const { return m_index; }
	
	void SetWeapon(Weapon *new_weapon) { m_weapon = new_weapon; }
	void SetItem(Item *new_item) { m_item = new_item; }
	bool HasItem() { return m_item; }
	
	/// @brief Checks if the player has pressed the 'grab' key.
	bool PressedGrab();
	
	/// @brief Construct a player in an initial position, and give it an index.
	/// @param initial_x Starting X position.
	/// @param initial_y Starting Y position.
	/// @param player_index Index given to the player. 
	Player(sf::Vector2f pos, int player_index);
private:
	void LoadBelly();
	void LoadKeys();
	
	Controls m_Input;
	int m_index, m_jumpcount, current_sprite;
	int m_jumpspeed;
	bool is_jumping, can_grab;
	
	Item *m_item;
	Weapon *m_weapon;
	sf::Sprite ms_belly;
	std::vector<sf::Texture> mt_belly;
};

#endif

