#ifndef ENTITIESFACADE_H
#define ENTITIESFACADE_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity/proyectile/Projectile.h"
#include "Escena/Match/World.h"
#include "Entity/Item/Weapon/Weapon.h"
#include "Entity/Item/Item.h"
#include "Entity/Player.h"
#include "Entity/Entity.h"
#include <string>

class EntitiesFacade {
public:
	EntitiesFacade(float width, float height, std::string map_name);
	~EntitiesFacade();
	void Update();
	void Draw(sf::RenderWindow &win);
	
	std::vector<Player*> GetPlayers() { return m_players; }
private:
	#include "Escena/Match/EntitiesFacadeTemplates.h"
	int UpdateEntity(Entity* entity);
	void PlayersUpdate();
	void ItemsUpdate();
	void WeaponsUpdate();
	void ProjectilesUpdate();
	void EraseUnusedProjectiles();
	
	std::vector<Player*> m_players;
	std::vector<Item*> m_items;
	std::vector<Weapon*> m_weapons;
	std::vector<Projectile*> m_projectiles;
	World m_world;
	
	std::vector<float> m_respawners;
	sf::Clock m_gameclock;
	
	float m_width, m_height;
};


#endif

