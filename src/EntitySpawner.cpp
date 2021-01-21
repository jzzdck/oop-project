#include "EntitySpawner.h"
#include "Utils/generalUtils.h"
#include <cstdlib>
using namespace std;

EntitySpawner::EntitySpawner(const sf::Vector2f &winsize) {
	m_winsize = winsize;
}

Player * EntitySpawner::SpawnPlayer (const sf::Vector2f & pos, int player_index) {
	return new Player(pos, player_index);
}

Flag * EntitySpawner::SpawnFlag (const sf::Vector2f & pos, int player_index) {
	return new Flag(pos, player_index);
}

Weapon * EntitySpawner::SpawnWeapon (const sf::Vector2f & pos, int index) {
	Weapon* new_weapon;
	
	switch (index) {
	case 0:
		new_weapon = new Shovel     ( pos );
		break;
	case 1:
		new_weapon = new Revolver   ( pos, 1);
		break;
	case 2:
		new_weapon = new Handcannon ( pos, 1);
	};
	
	return new_weapon;
}

Weapon * EntitySpawner::RandomWeapon ( ) {
	Weapon* new_weapon;
	int index = rand()%3;
	
	switch (index) {
	case 0:
		new_weapon = new Shovel     ( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf()} );
		break;
	case 1:
		new_weapon = new Revolver   ( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf()}, 1);
		break;
	case 2:
		new_weapon = new Handcannon ( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf()}, 1);
	};
	
	return new_weapon;
}

Item * EntitySpawner::RandomItem ( ) {
	Item* new_weapon;
	int index = rand()%1;
	
	switch (index) {
	case 0:
		new_weapon = new Flag( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf() }, rand()%2 );
		break;
	};
	
	return new_weapon;
}

