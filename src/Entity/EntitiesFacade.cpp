#include "EntitiesFacade.h"
#include "Player.h"
#include "Item/Weapon/Shovel.h"
#include "Item/Weapon/Revolver.h"
#include "Item/Weapon/Handcannon.h"
#include "Item/Flag.h"

EntitiesFacade::EntitiesFacade(float width, float height, std::string map_name) :
	m_world(width, height, 0.7, map_name), m_width(width), m_height(height)
{
	m_respawners.resize(2, 0.00f);
	m_players.push_back(new Player({m_width*0.9f, m_height*0.9f} , 0) );
	m_players.push_back(new Player({m_width*0.15f, m_height*0.4f}, 1) );
	
	int randsize = 30;
	
	for (size_t i=0; i<randsize; ++i) {
		int chance = rand()%101;
		if (chance < 25)
			m_weapons.push_back(new Shovel({m_width*utils::randf(), m_height*utils::randf()}));
		else if (chance < 50)
			m_weapons.push_back(new Revolver({m_width*utils::randf(), m_height*utils::randf()}, 1.f));
		else if (chance < 75)
			m_weapons.push_back(new Handcannon({m_width*utils::randf(), m_height*utils::randf()}, 1.f));
		else if (chance < 87)
			m_items.push_back(new Flag({m_width*utils::randf(), m_height*utils::randf()}, 1));
		else
			m_items.push_back(new Flag({m_width*utils::randf(), m_height*utils::randf()}, 0));
	}
}

void EntitiesFacade::Update ( ) {
	m_world.Update();	
	PlayersUpdate();
	ItemsUpdate();
	WeaponsUpdate();
	ProjectilesUpdate();
}

void EntitiesFacade::Draw (sf::RenderWindow & win) {
	for (Player *player : m_players) player->Draw(win);
	for (Item *item : m_items) item->Draw(win);
	for (Weapon *weapon : m_weapons) weapon->Draw(win);
	for (Projectile *projectile : m_projectiles) projectile->Draw(win);
	m_world.Draw(win);
}

void EntitiesFacade::WeaponsUpdate ( ) {
	m_weapons = EraseUnbounded(m_weapons);
	UpdateOwnerships(m_weapons);
	
	for (Weapon *weapon : m_weapons) {
		if (weapon->Owner() != -1) {
			Player *owner = m_players[weapon->Owner()];
			weapon->SetPos(owner->GetSprite().getGlobalBounds(), owner->GetFacing());
		}
		
		if (weapon->IsAttacking())
			m_projectiles.push_back(weapon->GetProjectile());
	}
}

void EntitiesFacade::PlayersUpdate ( ) {
	for (Player *player : m_players) {
		UpdateEntity(player);
		
		if (utils::IsUnbounded(player->GetSprite().getGlobalBounds(), {m_width, m_height}))
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

void EntitiesFacade::ProjectilesUpdate ( ) {
	EraseUnusedProjectiles();
	m_projectiles = EraseUnbounded(m_projectiles);
	for (Projectile *projectile : m_projectiles) {
		for (Player *player : m_players)
			if (projectile->CollidesWith(player->GetSprite()) && player->IsAlive())
				projectile->ApplyEffect(player);
	}
}

void EntitiesFacade::EraseUnusedProjectiles ( ) {
	for (size_t i=0; i<m_projectiles.size(); ++i) {
		if (!m_projectiles[i]->IsUsed()) {
			delete m_projectiles[i];
			m_projectiles[i] = nullptr;
		}
	}
	
	std::vector<Projectile*> new_objects;
	for (size_t i=0; i<m_projectiles.size(); ++i)
		if (m_projectiles[i]) 
			new_objects.push_back(m_projectiles[i]);
	
	m_projectiles = new_objects;
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

void EntitiesFacade::ItemsUpdate ( ) {
	m_items = EraseUnbounded(m_items);
	UpdateOwnerships(m_items);
}

int EntitiesFacade::UpdateEntity (Entity * entity) { 
	sf::Vector2f response;
	
	entity->Update();
	entity->ApplyGravity(m_world.GetGravity());
	
	int collision = m_world.CollidesWith(entity, response), base_col = -1;
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
