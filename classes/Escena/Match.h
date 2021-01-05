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

/** @brief The Match class handles the connection between the elements of the game; 
		World, Player, Weapon, etc.
**/

class Match : public Escena {
	std::vector<Player*> m_players;
	std::vector<Item*> m_items;
	std::vector<Weapon*> m_weapons;
	World m_world;
	
	sf::View m_view;
public:
	void ProcessEvent(sf::Event& e,Game& g)override;
	void Update(Game & g);
	void UpdateCamera();
	
	template<class T>
	int UpdateEntity(T* entity) { 
		sf::Vector2f response;
		entity->Update();
		entity->ApplyGravity(m_world.GetGravity());
		
		int base_col = -1;
		int coll_index = m_world.CollidesWith(entity->GetSprite(), response);
		while (coll_index != -1) {
			
			if (coll_index == m_world.GetBaseIndex(0))
				base_col = 0;
			else if (coll_index == m_world.GetBaseIndex(1))
				base_col = 1;
			
			entity->ApplyResponse(response);
			coll_index = m_world.CollidesWith(entity->GetSprite(), response, coll_index+1);
		} 
		
		return base_col;
	}
	
	template<class T> 
	void UpdateObjects(std::vector<T*> objects) {
		if (objects.empty()) return;
		
		for (T* object : objects) {
			UpdateEntity(object);
			if (object->Owner() != -1) 
				object->SetSpeed( {0,0} );
		}
		
		for (Player *player : m_players) {
			bool update = true, pressed_grab = player->PressedGrab(objects[0]);
			
			for (T* object : objects) {
				if (object->Owner() == -1 && 
					object->CollidesWith(*player) && pressed_grab) 
				{
					player->AssignObject(object);
					update = false;
					break;
				} 
			}
			
			if (update) for (T* object : objects) {
				if (object->Owner() == player->GetIndex() && pressed_grab)
					player->UnassignObject(object);
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

