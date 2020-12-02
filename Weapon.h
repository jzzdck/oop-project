#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "Entity.h"

class Weapon : public Entity {
public:
	Weapon(int damage, bool facing, float wdt);
	void SetPos(const sf::Vector2f &relative_to, bool facing);
	void SetText();
	virtual void Attack() = 0;
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	virtual ~Weapon() {}
protected:
	// this will probably be virtual in the future
	// different weapons may have different offsets from player
	sf::Vector2f OffSet(const sf::Vector2f &to_offset);
	sf::Vector2f m_pos;
	
	float m_width; 
	bool m_current; // left or right sprite
	int m_damage;
};

#endif

