#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "../Item.h"
#include "../../proyectile/Projectile.h"

class Projectile;

/// @brief Abstract class where all weapons inherit.
class Weapon : public Item {
public:
	/// @brief Draw the weapon in the current window
	virtual void Draw(sf::RenderWindow &win) = 0;
	
	virtual bool IsAttacking() {return attack_state;}
	void SetAttacking(bool state) { attack_state = state; }
	
	/// @brief Set the gun texture in relation to where the player is facing.
	void SetText();
	/// @brief Set the weapon position in relation to where the player is facing.
	void SetPos(const sf::Rect<float> &relative_to, bool facing);
	virtual Projectile* GetProjectile() = 0;
	
	/// @brief Construct a weapon in relation to where the player's facing.
	Weapon(sf::Vector2f pos, std::string keyword, int damage, bool facing, float wdt);
	
	/// @brief Virtual destructor; the class is abstract
	virtual ~Weapon() {}
protected:
	sf::Vector2f OffSet(const sf::Rect<float> &to_offset);
	
	sf::Clock firerate;
	float m_width; 
	bool m_current, attack_state = false;
	int m_damage;
	sf::Vector2f m_pos;
};

#endif
