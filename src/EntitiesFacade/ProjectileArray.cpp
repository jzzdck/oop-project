#include "ProjectileArray.h"
#include "PlayerInfo.h"
#include <cmath>
#include "../Entity/Projectile/Bullet.h"
#include "../Entity/Projectile/Bomb.h"
#include "../Entity/Projectile/MeleeHit.h"
#include "../Entity/Projectile/ElectricShot.h"

ProjectileArray::ProjectileArray(const sf::Vector2f &winsize) :
	EntityArray(winsize)
{
	
}

void ProjectileArray::ApplyProjectileData ( ) {
	for (ProjectileData data : current_data) {
		switch (data.projectile_index) {
		case -1:
			break;
		case 0:
			m_projectiles.push_back(new MeleeHit(data.weapon_position, data.direction));
			break;
		case 1:
			m_projectiles.push_back(new Bullet({20.f*data.direction, 0}, data.weapon_position, data.direction));
			break;
		case 2: {
			sf::Vector2f speed = {data.direction * 20.f * std::cos(data.handcannon_angle), -20.f * std::sin(data.handcannon_angle)};
			m_projectiles.push_back(new Bomb(speed, data.weapon_position, data.direction));
			break;
		} case 3:
			m_projectiles.push_back(new ElectricShot(data.weapon_position, data.direction));
			break;
		};
	}
	
	current_data.clear();
}

std::vector<PlayerInfo> ProjectileArray::UpdateArray (std::vector<PlayerInfo> & info, World & world) {
	m_projectiles = EraseUnused(m_projectiles, world);
	for (size_t i=0; i<info.size(); ++i)
		current_data.push_back(info.at(i).new_projectile);
	
	ApplyProjectileData();
	
	for (size_t i=0; i<m_projectiles.size(); ++i)
		Update(m_projectiles.at(i), world);
	
	return info;
}

void ProjectileArray::UpdateRegardingTo (PlayerInfo & info, Player * player, World & world) {
	for (Projectile* projectile : m_projectiles) {
		if (player->CollidesWith(projectile) && info.health_data.is_alive) {
			projectile->ApplyEffect(player);
			player->ApplyForce(projectile->GetPushbackForce());
		}
	}
}

void ProjectileArray::RenderWith (DrawingEnviroment & drawEnv) {
	for (Projectile *projectile : m_projectiles)
		projectile->Render(drawEnv), drawEnv.AddToLayer(projectile, 0);
}

ProjectileArray::~ProjectileArray ( ) {
	for(size_t i=0;i<m_projectiles.size();i++) 
		delete m_projectiles.at(i);
}

