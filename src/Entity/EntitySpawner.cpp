#include "EntitySpawner.h"
#include "../Utils/generalUtils.h"
#include <cstdlib>
#include "../TeslaGun.h"
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
		break;
	case 3:
		new_weapon = new TeslaGun (pos, 1);
		break;
	};
	
	return new_weapon;
}

Weapon * EntitySpawner::RandomWeapon ( ) {
	return SpawnWeapon( 
		{m_winsize.x * utils::randf(), m_winsize.y * utils::randf()},
		rand() % max_weapons
	);
}

Item * EntitySpawner::SpawnItem ( const sf::Vector2f & pos, int index ) {
	Item* new_weapon;
	
	switch (index) {
	case 0:
		new_weapon = new Flag( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf() }, rand()%2 );
		break;
	};
	
	return new_weapon;
}

Item * EntitySpawner::RandomItem ( ) {
	return SpawnItem( 
		{m_winsize.x * utils::randf(), m_winsize.y * utils::randf()},
		rand() % max_items
	);
}

