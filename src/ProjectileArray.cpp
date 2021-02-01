#include "ProjectileArray.h"
#include "Entity/proyectile/MeleeHit.h"
#include "Entity/proyectile/Bullet.h"
#include "Entity/proyectile/Bomb.h"
#include "ElectricShot.h"
#include "PlayerInfo.h"

ProjectileArray::ProjectileArray(const sf::Vector2f &winsize) :
	EntityArray(winsize)
{
	
}

void ProjectileArray::ApplyProjectileData ( ) {
	for (ProjectileData data : current_data) {
		sf::Vector2f mpos = { data.weapon_position.left, data.weapon_position.top};
		
		switch (data.projectile_index) {
		case -1:
			break;
		case 0:
			m_projectiles.push_back(new MeleeHit(mpos));
			break;
		case 1:
			m_projectiles.push_back(new Bullet({data.direction*20, 0}, mpos)); // dir
			break;
		case 2:
			m_projectiles.push_back(new Bomb({data.direction*20, 0}, mpos));
			break;
		case 3:
			m_projectiles.push_back(new ElectricShot({0,0,0,0}, mpos, data.direction));
			break;
		};
	}
	
	current_data.clear();
}

std::vector<PlayerInfo> ProjectileArray::UpdateArray (std::vector<PlayerInfo> & info, World & world) {
	m_projectiles = EraseUnused(m_projectiles, world);
	for (size_t i=0; i<info.size(); ++i) {
		current_data.push_back(info.at(i).new_projectile);
		info.at(i).new_projectile.projectile_index = -1;
	}
	
	ApplyProjectileData();
	
	for (size_t i=0; i<m_projectiles.size(); ++i)
		Update(m_projectiles.at(i), world);
	
	return info;
}

void ProjectileArray::UpdateRegardingTo (PlayerInfo & info, Player * player, World & world) {
	for (Projectile* projectile : m_projectiles)
		if (player->CollidesWith(projectile))
			projectile->ApplyEffect(player);
}

void ProjectileArray::RenderWith (DrawingEnviroment & drawEnv) {
	for (Projectile *projectile : m_projectiles)
		projectile->Render(drawEnv), drawEnv.AddToLayer(projectile, 0);
}

ProjectileArray::~ProjectileArray ( ) {
	for(size_t i=0;i<m_projectiles.size();i++) 
		delete m_projectiles.at(i);
}

