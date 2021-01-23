#ifndef ENTITYSPAWNER_H
#define ENTITYSPAWNER_H
#include "Player.h"
#include "Item/Weapon/Shovel.h"
#include "Item/Weapon/Revolver.h"
#include "Item/Weapon/Handcannon.h"
#include "Item/Flag.h"
#include "Item/Item.h"
#include "Item/Weapon/Weapon.h"

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
