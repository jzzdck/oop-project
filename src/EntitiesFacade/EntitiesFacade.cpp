#include "EntitiesFacade.h"
#include "PlayerUpdater.h"
#include "ItemArray.h"
#include "WeaponArray.h"
#include "ProjectileArray.h"
#include <algorithm>

EntitiesFacade::EntitiesFacade(float width, float height, std::string map_name) :
	m_world(width, height, 0.7, map_name)
{
	auto world_bounds = m_world.GetWorldBounds();
	sf::Vector2f world_size = {world_bounds.width, world_bounds.height};
	
	m_entity_arrays = {
		new PlayerUpdater(world_size),
		new ItemArray(world_size),
		new WeaponArray(world_size),
		new ProjectileArray(world_size)
	};
	
	m_infos.resize(2);	
	m_players.push_back(new Player(m_world.GetBaseSpawnPoint(0), 0));
	m_players.push_back(new Player(m_world.GetBaseSpawnPoint(1), 1));
	
	m_spawnlapse = sf::seconds(std::min(30.f*utils::randf(), 10.f));
	m_elapsed = sf::seconds(0);
}

void EntitiesFacade::Update ( const sf::Time &total_time ) {
	UpdatePlayerInfo();
	m_world.Update();
	
	for (EntityArray *updater : m_entity_arrays)
		m_infos = updater->UpdateArray(m_infos, m_world);
	
	for (Player* player : m_players)
		for (EntityArray *updater : m_entity_arrays)
			updater->UpdateRegardingTo(m_infos.at(player->GetIndex()), player, m_world);
	
	if (total_time - m_elapsed > m_spawnlapse) {
		m_spawnlapse = m_spawnlapse = sf::seconds(10.f*utils::randf());
		m_elapsed = total_time;
		SpawnSomethingAtRandom();
	}
}

void EntitiesFacade::Render (DrawingEnviroment& drawEnv) {
	for (EntityArray *drawer : m_entity_arrays)
		drawer->RenderWith(drawEnv);
	
	for (Player *player : m_players)
		player->Render(), drawEnv.AddToLayer(player, 4);
	
	m_world.Render(drawEnv);
}

void EntitiesFacade::ProcessPlayersEvents (sf::Event & e, Game & g) {
	for (Player *player : m_players)
		for (EntityArray *eventers : m_entity_arrays)
			eventers->ProcessPlayerEvents(m_infos.at(player->GetIndex()), player, e);
}

void EntitiesFacade::UpdatePlayerInfo() {
	for(size_t i=0;i<m_infos.size();i++) { 
		if (m_infos.at(i).weapon_index == -1) 
			m_infos.at(i).ammo_data =  {-1, -1};
		
		m_infos.at(i).health_data = m_players.at(i)->GetHealthData(); 
	}
}

CameraInfo EntitiesFacade::GetCameraInfo ( ) {
	std::vector<bool> living(2);
	std::vector<sf::Rect<float>> global_bounds(2);
	
	for(size_t i=0;i<living.size();i++) { 
		living.at(i) = m_players.at(i)->GetHealthData().is_alive;
		global_bounds.at(i) = m_players.at(i)->GetBounds();
	}
	
	return { living, global_bounds };
}

std::vector<PlayerInfo> EntitiesFacade::GetPlayersInfos ( ) {
	return m_infos;
}

EntitiesFacade::~EntitiesFacade ( ) {
	for (size_t i=0; i<m_players.size(); ++i) 
		delete m_players[i];
	
	for(size_t i=0;i<m_entity_arrays.size();i++) 
		delete m_entity_arrays.at(i);
}

std::vector<int> EntitiesFacade::GetRoundPoints ( ) {
	std::vector<int> aux;
	
	for(size_t i=0;i<m_infos.size();i++) 
		aux.push_back(m_infos.at(i).round_points);
	
	return aux;
}

void EntitiesFacade::SpawnSomethingAtRandom ( ) {
	bool spawnflag = utils::randf() < 0.60f;
	bool player = rand()%2;
	
	if (spawnflag && m_entity_arrays.at(1)->Size() < 1000) 
		m_entity_arrays.at(1)->SpawnAt(m_world.GetBaseSpawnPoint(player), player);
	
	int index = (utils::randf() > 0.6f) + 1; 
	if (utils::randf() <= 0.6f && m_entity_arrays.at(index)->Size() < 1000)
		m_entity_arrays.at(index)->SpawnRandom();
	
	if (utils::randf() <= 0.2f && m_entity_arrays.at(2)->Size() < 1000)
		m_entity_arrays.at(2)->SpawnRandom();
}

