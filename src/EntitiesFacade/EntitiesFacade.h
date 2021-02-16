#ifndef ENTITIESFACADE_H
#define ENTITIESFACADE_H
#include <string>
#include "../Game.h"
#include "../Entity/Player.h"
#include "PlayerInfo.h"
#include "EntityArray.h"
#include "World.h"

struct CameraInfo {
	std::vector<bool> living_states;
	std::vector<sf::Rect<float>> global_bounds;
};

class EntitiesFacade {
public:
	EntitiesFacade(float width, float height, std::string map_name);
	~EntitiesFacade();
	void Update(const sf::Time &total_time);
	void Render(DrawingEnviroment& drawEnv);
	void SpawnSomethingAtRandom();
	
	std::vector<PlayerInfo> GetPlayersInfos();
	std::vector<int> GetRoundPoints();
	CameraInfo GetCameraInfo();
	void ProcessPlayersEvents(sf::Event &e, Game &g);
private:
	void UpdatePlayerInfo();
	
	std::vector<EntityArray*> m_entity_arrays;
	std::vector<Player*> m_players;
	std::vector<PlayerInfo> m_infos;
	sf::Time m_spawnlapse, m_elapsed;
	World m_world;
};

#endif

