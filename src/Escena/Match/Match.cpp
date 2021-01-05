#include "Match.h"
#include <iostream>
#include <cmath>
#include "../../Utils/phutils.h"
#include "../Scene.h"
#include "../../Entity/Player.h"
#include "../../Entity/Item/Weapon/Shovel.h"
#include "../../Entity/Item/Weapon/Revolver.h"
#include "../../Entity/Item/Flag.h"
#include "../../Game.h"
#include "../Menu/Menu_Principal.h"

Match::Match(float width, float height) :
	Escena(width, height), m_world(width, height, 0.7)
{
	m_players.emplace_back(Player( {win_width*utils::randf(), win_height*0.4f} , 0) );
	m_players.emplace_back(Player( {win_width*0.15f, win_height*0.4f}, 1) );
	
	int randsize = rand()%(30-2) + 2;
	m_items.resize(randsize);
	for (size_t i=0; i<m_items.size(); ++i) { 
		int chance = rand()%101;
		if (chance < 33)
			m_items[i] = new Shovel( {win_width*utils::randf(), win_height*utils::randf()});
		else if (chance < 66)
			m_items[i] = new Revolver( {win_width*utils::randf(), win_height*utils::randf()}, 1, 32);
		else if (chance < 83)
			m_items[i] = new Flag( {win_width*utils::randf(), win_height*utils::randf()}, 1);
		else
			m_items[i] = new Flag( {win_width*utils::randf(), win_height*utils::randf()}, 0);
	}
}

void Match::ProcessEvent(sf::Event& e, Game& g) {
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		g.SetScene(new Menu_Principal(win_width, win_height));
}

void Match::Update (Game& g) {
	UpdateCamera();
	
	for (Player &player : m_players) {
		UpdatePlayer(player);
		UpdateOwnership(player, player.PressedGrab());
	}
	
	for (Item *item : m_items)
		UpdateItem(item);
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	win.setView(m_view);
	
	for (Player &player : m_players) 
		player.Draw(win);
	
	for (Item *item : m_items)
		item->Draw(win);
	
	m_world.Draw(win);
	win.display();
}

void Match::UpdatePlayer(Player &player) {
	sf::Vector2f response;
	player.ApplyGravity(m_world.GetGravity());
	player.Update();
	
	int coll_index = m_world.CollidesWith(player.GetSprite(), response);
	while (coll_index != -1 && player.GetSpeed().y != player.GetJumpSpeed()) {
		player.ApplyResponse(response);
		
		if (coll_index == m_world.GetBaseIndex(0) && player.GetIndex() == 0)
			std::cout << "Player 0 is at home base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(1) && player.GetIndex() == 0)
			std::cout << "Player 0 is at enemy base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(1) && player.GetIndex() == 1)
			std::cout << "Player 1 is at home base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(0) && player.GetIndex() == 1)
			std::cout << "Player 1 is at enemy base!" << std::endl;
		
		coll_index = m_world.CollidesWith(player.GetSprite(), response, coll_index+1);
	}
}

void Match::UpdateItem(Item *item) {
	sf::Vector2f response;
	item->Update();
	item->ApplyGravity(m_world.GetGravity());
	
	int coll_index = m_world.CollidesWith(item->GetSprite(), response);
	while (coll_index != -1) {
		item->ApplyResponse(response);
		coll_index = m_world.CollidesWith(item->GetSprite(), response, coll_index+1);
	}
	
	if (item->Owner() != -1) 
		item->SetSpeed( {0,0} ); // reset the speed if item has an owner
}

Match::~Match() {
	for (size_t i=0; i<m_items.size(); ++i) 
		delete m_items[i];
}

void Match::UpdateCamera () {
	auto sp0 = m_players[0].GetSprite().getGlobalBounds();
	auto sp1 = m_players[1].GetSprite().getGlobalBounds(); 
	
	sf::Vector2f center0 = utils::getCenter(sp0);
	sf::Vector2f center1 = utils::getCenter(sp1);
	
	sf::Vector2f cam_size = { 
		std::fabs(center1.x - center0.x),
		std::fabs(center1.y - center0.y) 
	};
	
	sf::Vector2f cam_center = { 
		cam_size.x/2.f + std::min(center0.x, center1.x), 
		cam_size.y/2.f + std::min(center0.y, center1.y)
	};
	
	m_view.setCenter(cam_center);
	m_view.setSize( {win_width, win_height} );
	
	float scale = std::max(cam_size.x/win_width + 0.2f, cam_size.y/win_height + 0.2f);
	scale = std::max(scale, 0.5f);
	m_view.zoom(scale);
}

void Match::UpdateOwnership(Player & player, bool pressed_grab) {
	bool col = false;
	
	for (Item *item : m_items) {
		if (item->Owner() == -1 && item->CollidesWith(player) && pressed_grab) {
			if (!col) col = true;
			
			if (item->IsWeapon()) {
				if (player.GetWeapon()) {
					player.GetWeapon()->SetOwner(-1);
					player.SetWeapon(nullptr);
				}
				
				player.SetWeapon(item);
				item->SetOwner(player.GetIndex());
			} else {
				if (player.GetItem()) {
					player.GetItem()->SetOwner(-1);
					player.SetItem(nullptr);
				}
				
				player.SetItem(item);
				item->SetOwner(player.GetIndex());
			}
			
			break;
		}
	}
	
	if (!col) for (Item* item : m_items) {
		if (item->Owner() == player.GetIndex() && pressed_grab) {
			if (item->IsWeapon())
				player.SetWeapon(nullptr);
			else
				player.SetItem(nullptr);
			
			item->SetOwner(-1);
			break;
		}
	}
}

