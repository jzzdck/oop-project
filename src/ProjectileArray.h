#ifndef PROJECTILEARRAY_H
#define PROJECTILEARRAY_H
#include "EntityArray.h"
#include "Entity/proyectile/Projectile.h"

class ProjectileArray : public EntityArray {
public:
	ProjectileArray(const sf::Vector2f &winsize);
	~ProjectileArray();
	std::vector<PlayerInfo> UpdateArray (std::vector<PlayerInfo> & info, World & world) override;
	void UpdateRegardingTo (PlayerInfo & info, Player * player, World & world) override;
	void RenderWith (DrawingEnviroment & drawEnv) override;
private:
	std::vector<Projectile*> m_projectiles;
	std::vector<ProjectileData> current_data;
	const int max_size = 4;
	void ApplyProjectileData();
	
	// not used:
	void SpawnRandom ( ) override {};
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override {};
	void ProcessPlayerEvents (PlayerInfo & info, Player * player, sf::Event & e) override {};
};

#endif

