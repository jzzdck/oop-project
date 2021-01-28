#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "../Item.h"
#include "../../proyectile/Projectile.h"

class Projectile;

/// @brief Abstract class where all weapons inherit.
class Weapon : public Item {
public:
	void Update() override;
	
	virtual bool IsAttacking() { return attack_state; }
	void SetAttacking(bool state) { attack_state = state; }
	sf::Vector2i GetAmmo() const { return {m_ammo, max_ammo}; }
	virtual Projectile* GetProjectile() = 0;
	
	/// @brief Construct a weapon in relation to where the player's facing.
	Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count);
	
	/// @brief Virtual destructor; the class is abstract
	virtual ~Weapon() {}
protected:
	sf::Vector2f OffSet(const sf::Rect<float> &to_offset);
	int m_ammo, max_ammo;
	
	sf::Clock firerate;
	bool attack_state = false;
	sf::Vector2f m_pos;
private:
	int PreviousOwner() const override { return -34404; }
	bool IsTheFlag() const override { return false; }
	int BelongsTo() const override { return -34404; }
};

#endif
