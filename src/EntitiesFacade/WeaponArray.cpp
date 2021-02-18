#include "WeaponArray.h"
#include <iostream>
#include "../Entity/Item/Weapon/Shovel.h"
#include "../Entity/Item/Weapon/Revolver.h"
#include "../Entity/Item/Weapon/Handcannon.h"
#include "../Entity/Item/Weapon/TeslaGun.h"
#include "../Utils/generalUtils.h"

WeaponArray::WeaponArray(const sf::Vector2f &winsize) : 
	EntityArray(winsize)
{
	size_t rands = rand()%20;
	for (size_t i=0; i<rands; ++i) 
		SpawnRandom();
}

void WeaponArray::SpawnAt (const sf::Vector2f & pos, int switch_index) {
	switch (switch_index) {
	case 0:
		m_weapons.push_back(new Shovel(pos));
		break;
	case 1:
		m_weapons.push_back(new Revolver(pos, 1));
		break;
	case 2:
		m_weapons.push_back(new Handcannon(pos, 1));
		break;
	case 3:
		m_weapons.push_back(new TeslaGun(pos, 1));
		break;
	};
}

void WeaponArray::SpawnRandom ( ) {
	SpawnAt(utils::randomPos({{0,0}, m_winsize}), rand()%max_size);
}

std::vector<PlayerInfo> WeaponArray::UpdateArray (std::vector<PlayerInfo> & info, World & world) {
	m_weapons = EraseUnused(m_weapons, world);
	
	for (size_t i=0; i<m_weapons.size(); ++i)
		Update(m_weapons.at(i), world);
	
	return info;
}

void WeaponArray::UpdateRegardingTo (PlayerInfo & info, Player * player, World & world) {
	for (Weapon *weapon : m_weapons) {
		if (weapon->Owner() == player->GetIndex()) {
			if (info.weapon_index == -1)
				weapon->SetOwner(-1, player->GetSpeed());
			
			weapon->SetPos(player->GetBounds(), player->GetFacing());
			weapon->SetAttacking(player->GetControls()["attack"]);
			info.ammo_data = weapon->GetAmmo();
			
			if (weapon->IsAttacking())
				info.new_projectile = weapon->GetProjectileData();
			
			break;
		}
	}
}

void WeaponArray::ProcessPlayerEvents (PlayerInfo & info, Player * player, sf::Event & e) {
	int collision = FirstToCollide(m_weapons, player, info.weapon_index);
	
	if (PlayerPressedGrab(player->GetControls(), e, false)) {
		if (collision != -1) {
			if (info.weapon_index != -1)
				m_weapons.at(info.weapon_index)->SetOwner(-1, player->GetSpeed());
			
			info.weapon_index = collision;
			m_weapons.at(collision)->SetOwner(player->GetIndex(), {0, 0});
		} else if (info.weapon_index != -1) {
			m_weapons.at(info.weapon_index)->SetOwner(-1, player->GetSpeed());
			info.weapon_index = -1;
		}
	}
}

void WeaponArray::RenderWith (DrawingEnviroment & drawEnv) {
	for (Weapon *weapon : m_weapons) {
		weapon->Render(drawEnv);
		drawEnv.AddToLayer(weapon, 3);
	}
}

WeaponArray::~WeaponArray ( ) {
	for (size_t i=0; i<m_weapons.size(); ++i) 
		delete m_weapons.at(i);
}

