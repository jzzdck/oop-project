#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "Entity.h"

class Weapon : public Entity {
public:
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	virtual void Attack() = 0;
	
	void SetText();
	void SetPos(const sf::Vector2f &relative_to, bool facing);
	
	Weapon(int damage, bool facing, float wdt);
	virtual ~Weapon() {}
protected:
	sf::Vector2f OffSet(const sf::Vector2f &to_offset);
	
	float m_width; 
	bool m_current;
	int m_damage;
	sf::Vector2f m_pos;
};

#endif

