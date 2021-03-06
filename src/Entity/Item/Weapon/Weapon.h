#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/System/Vector2.hpp>
#include "../Item.h"
#include "../../../EntitiesFacade/PlayerInfo.h"

class Weapon : public Item {
public:
	void Update() override;
	
	virtual bool IsAttacking() { return attack_state; }
	void SetAttacking(bool state) { attack_state = state; }
	Ammo GetAmmo() const { return m_ammo; }
	virtual ProjectileData GetProjectileData();
	
	Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count);	
	virtual ~Weapon() {}
protected:
	Ammo m_ammo;
	int projectile_index = -1;
	
	sf::Vector2f recoil;
	sf::Clock firerate;
	bool attack_state = false;
private:
	sf::Clock clock;
	sf::Time lifetime, released;
	bool start_time = false;
	int WasCaptured(int base_index) override { return -1; }
};

#endif
