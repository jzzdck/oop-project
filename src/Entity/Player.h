#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "Item/Weapon/Weapon.h"
#include "../Utils/Controls.h"
#include "Item/Item.h"
#include "../Escena/Match/Plataform/Plataform.h"
#include "../Game.h"

class Weapon;

/// @brief The Player class relates players' input to the game.
class Player : public Entity {
public:
	void ProcessEvents(sf::Event &e, Game &g);
	void Update() override; 
	void Draw(sf::RenderWindow &win) override;
	void ApplyResponse(const sf::Vector2f &vec) override;
	
	bool IsAlive() const {  return m_health > 0.0f; }
	void AssignHealth(float new_health) { m_health = new_health; }
	float GetHealth() const { return m_health; }
	int GetIndex() const { return m_index; }
	bool IsAttacking() { return m_input["attack"] && m_weapon; }
	Controls &GetControls() { return m_input;}
 	
	void UnassignObject(Item* if_item);
	void UnassignObject(Weapon* if_weapon);
	void UnassignObjects();
	
	void AssignObject(Item* new_item);
	void AssignObject(Weapon* new_weapon);
	
	Player(sf::Vector2f pos, int player_index);
private:
	void LoadKeys();
	
	int m_index;
	Controls m_input;
	
	int m_jumpcount, m_jumpspeed; 
	
	Item *m_item = nullptr;
	Weapon *m_weapon = nullptr; 
	
	float m_health = 1000.f;
	sf::Sprite ms_belly;
};

#endif

