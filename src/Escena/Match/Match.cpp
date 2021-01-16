#include "Match.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "../../Game.h"
#include "../../Entity/Player.h"
#include "../../Utils/generalUtils.h"
#include "../../Entity/Item/Weapon/Revolver.h"
#include "../../Entity/Item/Flag.h"
#include "../Menu/Menu_Principal.h"
#include "../Scene.h"
#include "../../Entity/Item/Weapon/Shovel.h"
#include "../../Entity/Item/Weapon/Handcannon.h"

Match::Match(float width, float height) :
	Escena(width, height), m_world(width, height, 0.7),
	m_pause(false)
{
	m_view.setCenter(win_width*utils::randf(), win_height*utils::randf());
	m_view.setSize(0,0);
	m_respawners.resize(2, 0.00f);
	m_players.push_back(new Player({win_width*utils::randf(), win_height*0.4f} , 0) );
	m_players.push_back(new Player({win_width*0.15f, win_height*0.4f}, 1) );
	
	int randsize = 30;
	
	for (size_t i=0; i<randsize; ++i)
	{ 
		int chance = rand()%101;
		if (chance < 25)
			m_weapons.push_back(new Shovel({win_width*utils::randf(), win_height*utils::randf()}));
		else if (chance < 50)
			m_weapons.push_back(new Revolver({win_width*utils::randf(), win_height*utils::randf()}, 1.f));
		else if (chance < 75)
			m_weapons.push_back(new Handcannon({win_width*utils::randf(), win_height*utils::randf()}, 1.f));
		else if (chance < 87)
			m_items.push_back(new Flag({win_width*utils::randf(), win_height*utils::randf()}, 1));
		else
			m_items.push_back(new Flag({win_width*utils::randf(), win_height*utils::randf()}, 0));
	}
}

void Match::ProcessEvent(sf::Event& e, Game& g) 
{
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		g.SetScene(new Menu_Principal(win_width, win_height));
	else
		if(e.type==sf::Event::KeyPressed && e.key.code == sf::Keyboard::P)
	{
		m_pause=!m_pause;
	}
}
void Match::EraseUnused ( std::vector<Projectile*> & projectiles) {
	for (size_t i=0; i<projectiles.size(); ++i) {
		if (!projectiles[i]->IsUsed()) {
			delete projectiles[i];
			projectiles[i] = nullptr;
		}
	}
	
	std::vector<Projectile*> new_objects;
	for (size_t i=0; i<projectiles.size(); ++i)
		if (projectiles[i]) 
			new_objects.push_back(projectiles[i]);
	
	projectiles = new_objects;
}

void Match::Update (Game& g) {
	if(!m_pause)
	{
		UpdateCamera();
		m_world.Update();
		
		for (Player *player : m_players) {
			UpdateEntity(player);
			
			if (IsUnbounded(player))
				player->AssignHealth(-1000.f); 
			
			if (!player->IsAlive()) {
				if (m_respawners[player->GetIndex()] == 0.00f)
					m_respawners[player->GetIndex()] = m_clock.getElapsedTime().asSeconds();
				player->UnassignObjects();
			}
		}
		
		for (size_t i=0; i<m_respawners.size(); ++i) {
			float can_respawn = m_clock.getElapsedTime().asSeconds() - m_respawners[i];
			if (!m_players[i]->IsAlive() && can_respawn >= 1.5f)
			{
				m_players[i]->GetSprite().setPosition(m_players[i]->GetInitPos());
				m_players[i]->SetSpeed({0, 0});
				m_players[i]->AssignHealth(1000.f);
				m_respawners[i] = 0.00f;
			}
		}
		
		m_items = EraseUnbounded(m_items);
		UpdateOwnerships(m_items);
		
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
		
		EraseUnused( m_projectiles );
		m_projectiles = EraseUnbounded(m_projectiles);
		for (Projectile *projectile : m_projectiles) {
			for (Player *player : m_players)
				if (projectile->CollidesWith(player->GetSprite()) && player->IsAlive())
					projectile->ApplyEffect(player);
		}
	}
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	win.setView(m_view);
	
	for (Player *player : m_players) player->Draw(win);
	for (Item *item : m_items) item->Draw(win);
	for (Weapon *weapon : m_weapons) weapon->Draw(win);
	for (Projectile *projectile : m_projectiles) projectile->Draw(win);
	
	m_world.Draw(win);
	win.display();
}

Match::~Match() {
	for (size_t i=0; i<m_players.size(); ++i) 
		delete m_players[i];
	
	for (size_t i=0; i<m_items.size(); ++i) 
		delete m_items[i];
	
	for (size_t i=0; i<m_weapons.size(); ++i) 
		delete m_weapons[i];
	
	for(size_t i=0;i<m_projectiles.size();i++)
		delete m_projectiles[i];
}

void Match::UpdateCamera () {
	sf::Vector2f prev_center = m_view.getCenter();
	sf::Vector2f target_center, cam_size;
	
	if (m_players[0]->IsAlive() && m_players[1]->IsAlive()) {
		auto sp0 = m_players[0]->GetSprite().getGlobalBounds();
		auto sp1 = m_players[1]->GetSprite().getGlobalBounds(); 
		
		sf::Vector2f center0 = utils::getCenter(sp0);
		sf::Vector2f center1 = utils::getCenter(sp1);
		
		cam_size = { 
			std::fabs(center1.x - center0.x),
			std::fabs(center1.y - center0.y) 
		};
		
		target_center = { 
			cam_size.x/2.f + std::min(center0.x, center1.x), 
			cam_size.y/2.f + std::min(center0.y, center1.y)
		};
	} else {
		for(size_t i=0;i<m_players.size();i++) { 
			if (m_players[i]->IsAlive()) {
				auto sp0 = m_players[i]->GetSprite().getGlobalBounds();
				target_center = utils::getCenter(sp0);
				prev_center = m_view.getCenter();
				cam_size = {sp0.width, sp0.height};
			}
		}
	}
	
	m_view.setCenter({ 
		prev_center.x*0.98f + target_center.x*0.02f,
		prev_center.y*0.98f + target_center.y*0.02f,
	});
	
	m_view.setSize( {win_width, win_height} );
	float aux = std::max(cam_size.x/win_width + 0.36f, cam_size.y/win_height + 0.36f);
	m_zoom = aux*0.05 + m_zoom*0.95;
	m_view.zoom(m_zoom);
}

