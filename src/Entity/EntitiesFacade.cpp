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
	PlayersUpdate();
	ItemsUpdate();
	WeaponsUpdate();
	ProjectilesUpdate();
}

void EntitiesFacade::Render (DrawingEnviroment& drawEnv) {
	for (Player *player : m_players) {
		player->Render();
		drawEnv.AddToLayer(player,2);
	}
	
	for (Item *item : m_items) {
		item->Render(drawEnv);
		drawEnv.AddToLayer(item,1);
	}
	
	for (Weapon *weapon : m_weapons) {
		weapon->Render(drawEnv);
		drawEnv.AddToLayer(weapon,1);
	}
	
	for (Projectile *projectile : m_projectiles) {
		projectile->Render(drawEnv);
		drawEnv.AddToLayer(projectile,3);
	}
	
	m_world.Render(drawEnv);
}

void EntitiesFacade::PlayersUpdate ( ) {
	for (Player *player : m_players) {
		UpdateEntity(player);
		
		if (utils::IsUnbounded(player->GetSprite().getGlobalBounds(), {m_width-100, m_height-100}))
			player->AssignHealth(-1000.f);
		
		if (!player->IsAlive() && m_respawners[player->GetIndex()] == 0.00f) {
			m_respawners[player->GetIndex()] = m_gameclock.getElapsedTime().asSeconds();
			player->UnassignObjects();
		}
	}
	
	for (size_t i=0; i<m_respawners.size(); ++i) {
		float can_respawn = m_gameclock.getElapsedTime().asSeconds() - m_respawners[i];
		if (!m_players[i]->IsAlive() && can_respawn >= 1.5f) {
			m_players[i]->GetSprite().setPosition(m_players[i]->GetInitPos());
			m_players[i]->SetSpeed({0, 0});
			m_players[i]->AssignHealth(1000.f);
			m_respawners[i] = 0.00f;
		}
	}
}

void EntitiesFacade::ItemsUpdate ( ) {
	for (size_t i=0; i<m_items.size(); ++i) { 
		int base_col = UpdateEntity(m_items[i]);
		
		if (m_items[i]->IsTheFlag() && base_col != -1) {
			int previous_owner = m_items[i]->PreviousOwner();
			bool was_stolen, taken_home;
			was_stolen = (m_items[i]->BelongsTo() != previous_owner);
			taken_home = (previous_owner == base_col);
			
			if (was_stolen && taken_home && previous_owner != -1)  {
				m_items[i]->SetUsing(false);
				m_roundpoints[previous_owner]++;
			}
		}
	}
	
	m_items = EraseUnbounded(m_items);
	m_items = EraseUnused(m_items);
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
		}
		
		if (weapon->IsAttacking())
			m_projectiles.push_back(weapon->GetProjectile());
	}
}

void EntitiesFacade::ProjectilesUpdate ( ) {
	for (size_t i=0; i<m_projectiles.size(); ++i)
		UpdateEntity(m_projectiles[i]);
	
	m_projectiles = EraseUnused(m_projectiles);
	m_projectiles = EraseUnbounded(m_projectiles);
	
	for (Projectile *projectile : m_projectiles) {
		for (Player *player : m_players)
			if (projectile->CollidesWith(player->GetSprite()) && player->IsAlive())
				projectile->ApplyEffect(player);
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
	for (Player * player : m_players) {
		player->ProcessEvents(e, g);
		
		Controls player_controls = player->GetControls();
		if (e.type == sf::Event::KeyPressed && e.key.code == player_controls.GetKey("grab")) {
			if (player_controls["down"])
				UpdateOwnerships(player, m_items);
			else
				UpdateOwnerships(player, m_weapons);
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
