#ifndef ENTITIESFACADE_H
#define ENTITIESFACADE_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "Entity.h"
#include "Player.h"
#include "Item/Item.h"
#include "proyectile/Projectile.h"
#include "../Escena/Match/World.h"
#include "../Game.h"
#include "../EntitySpawner.h"

class EntitiesFacade {
public:
	EntitiesFacade(float width, float height, std::string map_name);
	~EntitiesFacade();
	void Update();
	void Draw(sf::RenderWindow &win);
	
	std::vector<Player*> GetPlayers() { return m_players; }
	std::vector<int> GetRoundState() { return m_roundpoints; }
	void ProcessPlayersEvents(sf::Event &e, Game &g);
private:
// private methods:
	#include "../Escena/Match/EntitiesFacadeTemplates.h"
	int UpdateEntity(Entity* entity);
	void PlayersUpdate();
	void ItemsUpdate();
	void WeaponsUpdate();
	void ProjectilesUpdate();
	void EraseUnusedProjectiles();
	
// atributes:
	EntitySpawner m_spawner;
	std::vector<int> m_roundpoints;
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

