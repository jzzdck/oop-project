#ifndef WEAPONARRAY_H
#define WEAPONARRAY_H
#include "EntityArray.h"
#include "../Entity/Item/Weapon/Weapon.h"

class WeaponArray : public EntityArray {
public:
	WeaponArray(const sf::Vector2f &winsize);
	~WeaponArray();
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override;
	void SpawnRandom ( ) override;
	size_t Size() const override { return m_weapons.size(); } 
	std::vector<PlayerInfo> UpdateArray (std::vector<PlayerInfo> & info, World & world) override;
	void UpdateRegardingTo (PlayerInfo & info, Player * player, World & world) override;
	void ProcessPlayerEvents (PlayerInfo & info, Player * player, sf::Event & e) override;
	void RenderWith (DrawingEnviroment & drawEnv) override;
private:
	std::vector<Weapon*> m_weapons;
	const int max_size = 4;
};

#endif

