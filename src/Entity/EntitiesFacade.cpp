#include "EntitiesFacade.h"
#include "Player.h"
#include "Item/Weapon/Shovel.h"
#include "Item/Weapon/Revolver.h"
#include "Item/Weapon/Handcannon.h"
#include "Item/Flag.h"
#include "../PlayerUpdater.h"

EntitiesFacade::EntitiesFacade(float width, float height, std::string map_name) :
	m_world(width, height, 0.7, map_name)
{
	m_entity_arrays = {
		new PlayerUpdater({width, height})
	};
	
	m_infos.resize(2);	
	m_players.push_back(new Player({width*0.9f, height*0.9f} , 0));
	m_players.push_back(new Player({width*0.15f, height*0.4f}, 1));
}

void EntitiesFacade::Update ( ) {
	m_world.Update();
	
	for(Player* player : m_players)
		for (EntityArray *updater : m_entity_arrays)
			updater->UpdateRegardingTo(player, m_world);
	
	UpdatePlayerInfo();
}

void EntitiesFacade::Render (DrawingEnviroment& drawEnv) {
	for (EntityArray *drawer : m_entity_arrays)
		drawer->RenderWith(drawEnv);
	
	for (Player *player : m_players)
		player->Render(), drawEnv.AddToLayer(player, 2);
	
	m_world.Render(drawEnv);
}

void EntitiesFacade::ProcessPlayersEvents (sf::Event & e, Game & g) {
	for (size_t i=0; i<m_players.size(); ++i)
		m_entity_arrays.at(0)->ProcessPlayerEvents(m_players.at(i), e, g);
}

void EntitiesFacade::UpdatePlayerInfo() {
	for(size_t i=0;i<m_infos.size();i++) { 
		if (m_infos.at(i).weapon_index == -1) 
			m_infos.at(i).ammo_data =  {-1, -1};
//		else
//			m_infos.at(i).ammo_data = m_entity_arrays.at(2)[weapon_index]->GetAmmo();
		
		m_infos.at(i).health_data = m_players.at(i)->GetHealthData(); 
	}
}

CameraInfo EntitiesFacade::GetCameraInfo ( ) {
	std::vector<bool> living(2);
	std::vector<sf::Rect<float>> global_bounds(2);
	
	for(size_t i=0;i<living.size();i++) { 
		living.at(i) = m_players.at(i)->GetHealthData().is_alive;
		global_bounds.at(i) = m_players.at(i)->GetSprite().getGlobalBounds();
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
