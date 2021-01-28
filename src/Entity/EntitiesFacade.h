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
#include "EntitySpawner.h"
#include "../EntityArray.h"

struct PlayerInfo {
	int weapon_index = -1;
	int item_index = -1;
	int round_points = 0;
	
	Ammo ammo_data;
	HealthData health_data;
};

struct CameraInfo {
	vector<bool> living_states;
	vector<sf::Rect<float>> global_bounds;
};

class EntitiesFacade {
public:
	EntitiesFacade(float width, float height, std::string map_name);
	~EntitiesFacade();
	void Update();
	void Render(DrawingEnviroment& drawEnv);
	
	std::vector<PlayerInfo> GetPlayersInfos();
	CameraInfo GetCameraInfo();
	void ProcessPlayersEvents(sf::Event &e, Game &g);
private:
// private methods:
	int UpdateEntity(Entity* entity);
	void UpdatePlayerInfo();
	
// atributes:
	std::vector<EntityArray*> m_entity_arrays;
	std::vector<Player*> m_players;
	std::vector<PlayerInfo> m_infos;
	World m_world;
};

#endif

