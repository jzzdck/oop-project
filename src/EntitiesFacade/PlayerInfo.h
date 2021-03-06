#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <vector>
#include "../Entity/Player.h"

struct Ammo {
	int max;
	int current;
	
	Ammo() : max(-1), current(-1) {}
	Ammo(int m, int c) : max(m), current(c) {}
};

struct ProjectileData {
	sf::Rect<float> weapon_position;
	int projectile_index = -1;
	float direction;
	float handcannon_angle;
	sf::Vector2f recoil;
};

struct PlayerInfo {
	int weapon_index = -1;
	int item_index = -1;
	int round_points = 0;
	
	Ammo ammo_data;
	HealthData health_data;
	
	ProjectileData new_projectile;
};

#endif
