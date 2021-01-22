#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H
#include "Entity/Player.h"
#include "Entity/Item/Item.h"
#include "Entity/Item/Flag.h"
#include "Entity/Item/Weapon/Shovel.h"
#include "Entity/Item/Weapon/Revolver.h"
#include "Entity/Item/Weapon/Handcannon.h"

class EntitySpawner {
public:
	EntitySpawner		 (const sf::Vector2f &winsize);
	Player * SpawnPlayer (const sf::Vector2f &pos, int player_index);
	Flag   * SpawnFlag   (const sf::Vector2f &pos, int player_index);
	Item   * SpawnItem   (const sf::Vector2f &pos, int        index);
	Weapon * SpawnWeapon (const sf::Vector2f &pos, int        index);
	
	Item   * RandomItem();
	Weapon * RandomWeapon();
private:
	sf::Vector2f m_winsize;
	int max_items = 1, max_weapons = 3;
};

#endif
