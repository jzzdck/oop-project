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
#include "../../Entity/Player.h"
#include "../../Entity/proyectile/Projectile.h"

/** @brief The Match class handles the connection between the elements of the game 
World, Player, Weapon, etc.
**/

class Match : public Escena {
	std::vector<Player*> m_players;
	std::vector<Item*> m_items;
	std::vector<Weapon*> m_weapons;
	std::vector<Projectile*> m_projectiles;
	sf::Clock m_clock;
	std::vector<float> m_respawners;
	World m_world;
	
	sf::View m_view;
public:
	#include "MatchTemplates.h"
	void ProcessEvent(sf::Event& e,Game& g)override;
	void Update(Game & g);
	void UpdateCamera();
	/// @brief Draw the Match's elements in the window.
	/// @param win The window where to draw.
	void Draw(sf::RenderWindow & win);
	
	void EraseUnused(std::vector<Projectile*> &projectiles);
	
	/// @brief Construct the match
	/// @param width Match uses this parameter to set the X position of its elements.
	/// @param height Match uses this parameter to set the Y position of its elements.
	Match(float width, float height);
	/// @brief Items are dynamic memory and should be deleted.
	~Match();
};

#endif

