#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include "Entity/Player.h"
#include "Entity/Item/Weapon/Weapon.h"

struct PlayerInfo {
	int weapon_index = -1;
	int item_index = -1;
	int round_points = 0;
	
	Ammo ammo_data;
	HealthData health_data;
};

#endif
