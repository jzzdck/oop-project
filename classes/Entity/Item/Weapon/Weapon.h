#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "../Item.h"

/// @brief Abstract class where all weapons inherit.
class Weapon : public Item {
public:
	bool IsWeapon() const override { return true; }
	
	/// @brief Draw the weapon in the current window
	virtual void Draw(sf::RenderWindow &win) = 0;
	/// @brief Virtual method for attacking.
	virtual void Action() = 0;
	
	/// @brief Set the gun texture in relation to where te player is facing.
	void SetText();
	/// @brief Set the weapon position in relation to where the player is facing.
	void SetPos(const sf::Vector2f &relative_to, bool facing);
	
	/// @brief Construct a weapon in relation to where the player's facing.
	Weapon(sf::Vector2f pos, std::string keyword, int damage, bool facing, float wdt);
	
	/// @brief Virtual destructor; the class is abstract
	virtual ~Weapon() {}
protected:
	/// @brief Get an offset the weapon's sprite in relation to a position.
	/// This method is used to offset the weapon from the player.
	/// @param to_offset Offset is applied from this position.
	/// @return The vector that should be applied to the current Weapon position.
	sf::Vector2f OffSet(const sf::Vector2f &to_offset);
	
	float m_width; 
	bool m_current;
	int m_damage;
	sf::Vector2f m_pos;
};

#endif

