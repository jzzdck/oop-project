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
#include "../Animation.h"

class Weapon;

struct Jump {
	int count;
	int speed;
};

struct HealthData {
	const float max_health = 1000.f;
	float current_health = 1000.f;
	bool is_alive = true;
};

/// @brief The Player class relates players' input to the game.
class Player : public Entity {
public:
	void ProcessEvents(sf::Event &e, Game &g);
	void Update() override; 
	void Render() override;
	void RelocateSprites();
	
	void ApplyResponse(const sf::Vector2f &vec) override;
	
	HealthData &GetHealthData() { return m_health; };
	HealthData  GetHealthData() const { return m_health; };
	int GetIndex() const { return m_index; }
	bool IsAttacking() { return m_input["attack"] && m_weapon; }
	Controls &GetControls() { return m_input;}
	sf::Vector2i GetAmmo() const;
 	
	void UnassignObject(Item* if_item);
	void UnassignObject(Weapon* if_weapon);
	void UnassignObjects();
	
	void AssignObject(Item* new_item);
	void AssignObject(Weapon* new_weapon);
	
	Player(sf::Vector2f pos, int player_index);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void LoadKeys();
	
	int m_index;
	Controls m_input;
	
	Jump m_jump; 
	Animation m_animation;
	
	Item *m_item = nullptr;
	Weapon *m_weapon = nullptr; 
	
	HealthData m_health;
	sf::Sprite ms_belly;
};

#endif

