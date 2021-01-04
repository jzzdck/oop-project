#ifndef MATCH_H
#define MATCH_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Scene.h"
#include <vector>
#include "../Entity/Player.h"
#include "World.h"
#include "../Entity/Item/Weapon/Shovel.h"
#include "../Entity/Item/Weapon/Revolver.h"
#include "../Entity/Item/Flag.h"
#include "../Entity/Item/Weapon/Weapon.h"

class World;

/** @brief The Match class handles the connection between the elements of the game; 
		World, Player, Weapon, etc.
**/

class Match : public Escena {
	std::vector<Player> m_players;
	std::vector<Item*> m_items;
	std::vector<Weapon*> m_weapons;
	World m_world;
	
	sf::View m_view;
public:
	void ProcessEvent(sf::Event& e,Game& g)override;
	
	void Update(Game & g);
	
	void UpdateCamera();
	void UpdatePlayer(Player &player);
	
	template<class T>
	void UpdateObject(T* object) {
		sf::Vector2f response;
		object->Update();
		object->ApplyGravity(m_world.GetGravity());
		
		int coll_index = m_world.CollidesWith(object->GetSprite(), response);
		while (coll_index != -1) {
			object->ApplyResponse(response);
			coll_index = m_world.CollidesWith(object->GetSprite(), response, coll_index+1);
		}
		
		if (object->Owner() != -1) 
			object->SetSpeed( {0,0} ); // reset the speed if item has an owner
	}
	
	template<class T> 
	void UpdateObjects(std::vector<T*> objects) {
		for (T* object : objects)
			UpdateObject(object);
		
		for (Player &player : m_players) {
			bool update = true, col = true;
			bool pressed_grab = player.PressedGrab(objects[0]);
			
			for (T* object : objects) {
				if (update) { 
					if (object->Owner() == -1 && object->CollidesWith(player) && pressed_grab) {
						player.AssignObject(object);
						update = false;
					} 
				} else { col = false; break; }
			}
			
			if (col) for (T* object : objects) {
				if (update) {
					if (object->Owner() == player.GetIndex() && pressed_grab) 
						player.UnassignObject(object);
				} else break;
			}
		}
	}
	
	/// @brief Draw the Match's elements in the window.
	/// @param win The window where to draw.
	void Draw(sf::RenderWindow & win);
	
	/// @brief Construct the match
	/// @param width Match uses this parameter to set the X position of its elements.
	/// @param height Match uses this parameter to set the Y position of its elements.
	Match(float width, float height);
	/// @brief Items are dynamic memory and should be deleted.
	~Match();
};

#endif
