#include "EntitiesFacade.h"
#include "Player.h"
#include "Item/Weapon/Shovel.h"
#include "Item/Weapon/Revolver.h"
#include "Item/Weapon/Handcannon.h"
#include "Item/Flag.h"

EntitiesFacade::EntitiesFacade(float width, float height, std::string map_name) :
	m_world(width, height, 0.7, map_name), 
	m_spawner( {width, height} ),
	m_width(width), m_height(height)
{
	m_ownerships.resize(2);
	m_respawners.resize(2, 0.00f);
	m_players.push_back(m_spawner.SpawnPlayer({m_width*0.9f, m_height*0.9f} , 0));
	m_players.push_back(m_spawner.SpawnPlayer({m_width*0.15f, m_height*0.4f}, 1));
	m_roundpoints.assign(m_players.size(), 0);
	
	size_t randitems = rand()%15 + 5, randweapons = rand()%20;
	for (size_t i=0; i<randitems; ++i)
		m_items.push_back(m_spawner.RandomItem());
	
	for (size_t i=0; i<randweapons; ++i)
		m_weapons.push_back(m_spawner.RandomWeapon());
}

void EntitiesFacade::Update ( ) {
	m_world.Update();
	
	for(Player* player : players)
		for (EntityArray *updater : updaters)
			updater->UpdateWith(player);
	
	PlayersUpdate();
	ItemsUpdate();
	WeaponsUpdate();
	ProjectilesUpdate();
}

void EntitiesFacade::Render (DrawingEnviroment& drawEnv) {
	for (EntityArray *drawer : updaters)
		drawer->RenderWith(drawEnv);
	
	for (Player *player : m_players) {
		player->Render();
		drawEnv.AddToLayer(player,2);
	}
	
	for (Item *item : m_items) {
		item->Render(drawEnv);
		drawEnv.AddToLayer(item,3);
	}
	
	for (Weapon *weapon : m_weapons) {
		weapon->Render(drawEnv);
		drawEnv.AddToLayer(weapon,3);
	}
	
	for (Projectile *projectile : m_projectiles) {
		projectile->Render(drawEnv);
		drawEnv.AddToLayer(projectile,8);
	}
	
	m_world.Render(drawEnv);
}

void EntitiesFacade::PlayersUpdate ( ) {
	for (Player *player : m_players) {
		HealthData &h = player->GetHealthData();
		UpdateEntity(player);
		
		if (utils::IsUnbounded(player->GetSprite().getGlobalBounds(), {m_width-100, m_height-100}))
			h.current_health = -1000.f;
		
		if (!h.is_alive && m_respawners[player->GetIndex()] == 0.00f)
			m_respawners[player->GetIndex()] = m_gameclock.getElapsedTime().asSeconds();
	}
	
	for (size_t i=0; i<m_respawners.size(); ++i) {
		HealthData &aux = m_players[i]->GetHealthData();
		float can_respawn = m_gameclock.getElapsedTime().asSeconds() - m_respawners[i];
		if (!aux.is_alive && can_respawn >= 1.5f) {
			m_players[i]->GetSprite().setPosition(m_players[i]->GetInitPos());
			m_players[i]->SetSpeed({0, 0});
			aux.current_health = 1000.f;
			aux.is_alive = true;
			m_respawners[i] = 0.00f;
		}
	}
}

void EntitiesFacade::ItemsUpdate ( ) {
	for (size_t i=0; i<m_items.size(); ++i) { 
		int base_col = UpdateEntity(m_items[i]);
		int who_captured = m_items[i]->WasCaptured(base_col);
		
		if (who_captured != -1)
			m_roundpoints.at(who_captured)++; 
	}
	
	m_items = EraseUnbounded(m_items);
	m_items = EraseUnused(m_items);
	
	for (Item *item : m_items) {
		if (item->Owner() != -1) {
			Player *owner = m_players[item->Owner()];
			item->SetPos(owner->GetSprite().getGlobalBounds(), owner->GetFacing());
		}
	}
}

void EntitiesFacade::WeaponsUpdate ( ) {
	for (size_t i=0; i<m_weapons.size(); ++i) 
		UpdateEntity(m_weapons[i]);
	
	m_weapons = EraseUnused(m_weapons);
	m_weapons = EraseUnbounded(m_weapons);
	
	for (Weapon *weapon : m_weapons) {
		if (weapon->Owner() != -1) {
			Player *owner = m_players[weapon->Owner()];
			weapon->SetPos(owner->GetSprite().getGlobalBounds(), owner->GetFacing());
			weapon->SetAttacking(owner->GetControls()["attack"]);
			
			if (weapon->IsAttacking())
				m_projectiles.push_back(weapon->GetProjectile());
		}
	}
}

void EntitiesFacade::ProjectilesUpdate ( ) {
	for (size_t i=0; i<m_projectiles.size(); ++i)
		UpdateEntity(m_projectiles[i]);
	
	m_projectiles = EraseUnused(m_projectiles);
	m_projectiles = EraseUnbounded(m_projectiles);
	
	for (Projectile *projectile : m_projectiles) {
		for (Player *player : m_players) {
			HealthData &h = player->GetHealthData(); 
			if (projectile->CollidesWith(player->GetSprite()) && h.is_alive)
				projectile->ApplyEffect(player);
		}
	}
}

int EntitiesFacade::UpdateEntity (Entity * entity) { 
	sf::Vector2f response;
	
	entity->Update();
	entity->ApplyGravity(m_world.GetGravity());
	
	int collision = m_world.CollidesWith(entity, response), base_col = -1;
	if (collision == -1) entity->SetPlatform(nullptr);
	
	while (collision != -1) {
		if (collision == m_world.GetBaseIndex(0))
			base_col = 0;
		else if (collision == m_world.GetBaseIndex(1))
			base_col = 1;
		
		entity->ApplyResponse(-response);
		collision = m_world.CollidesWith(entity, response, collision+1);
	}
	
	return base_col;
}

void EntitiesFacade::ProcessPlayersEvents (sf::Event & e, Game & g) {
	for (size_t i=0; i<m_players.size(); ++i) {
		m_players.at(i)->ProcessEvents(e, g);
		
		Controls player_controls = m_players.at(i)->GetControls();
		if (e.type == sf::Event::KeyPressed && e.key.code == player_controls.GetKey("grab")) {
			if (player_controls["down"])
				UpdateOwnerships(m_ownerships.at(i).item_index, m_players.at(i), m_items);
			else
				UpdateOwnerships(m_ownerships.at(i).weapon_index, m_players.at(i), m_weapons);
		}
	}
}

EntitiesFacade::~EntitiesFacade ( ) {
	for (size_t i=0; i<m_players.size(); ++i) 
		delete m_players[i];
	
	for (size_t i=0; i<m_items.size(); ++i) 
		delete m_items[i];
	
	for (size_t i=0; i<m_weapons.size(); ++i) 
		delete m_weapons[i];
	
	for(size_t i=0;i<m_projectiles.size();i++)
		delete m_projectiles[i];
}

std::vector<HUDinfo> EntitiesFacade::GetHUDinfo ( ) {
	std::vector<HUDinfo> info;
	info.resize(2);
	
	for (size_t i=0; i<info.size(); ++i) { 
		info.at(i).health_data = m_players.at(i)->GetHealthData();
		info.at(i).round_data = m_roundpoints.at(i);
		
		if (m_ownerships.at(i).weapon_index != -1)
			info.at(i).ammo_data = m_weapons.at(m_ownerships.at(i).weapon_index)->GetAmmo();
		else
			info.at(i).ammo_data = {1, -1};
	}
	
	return info;
}
