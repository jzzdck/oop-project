#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "../Item.h"
#include "../../proyectile/Projectile.h"

struct Ammo {
	int max;
	int current;
	
	Ammo() : max(-1), current(-1) {}
	Ammo(int m, int c) : max(m), current(c) {}
};

class Weapon : public Item {
public:
	void Update() override;
	
	virtual bool IsAttacking() { return attack_state; }
	void SetAttacking(bool state) { attack_state = state; }
	Ammo GetAmmo() const { return m_ammo; }
	virtual Projectile* GetProjectile() = 0;
	
	Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count);	
	virtual ~Weapon() {}
protected:
	Ammo m_ammo;
	
	sf::Clock firerate;
	bool attack_state = false;
private:
	int WasCaptured(int base_index) override { return -1; }
};

#endif
