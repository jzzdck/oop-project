#include "Match.h"
#include "Game.h"
#include "Flag.h"
#include <iostream>
#include "Revolver.h"
#include "Shovel.h"

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

void Match::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		g.SetScene(new Menu_Principal(win_width, win_height));
	
	for (Player &player : m_players)
		UpdatePlayer(player);
	
	for (Item *item : m_items) 
		UpdateItem(item);
	
	// this doesnt belong to player nor item, so its a separated for
	for (Player &player : m_players) {
		bool col = false, pressed_grab = player.PressedGrab();
		
		for (Item *item : m_items) {
			if (item->Owner() == -1 && item->CollidesWith(player) && pressed_grab) {
				if (!col) col = true;
				
				if (item->IsWeapon()) {
					if (player.HasWeapon()) {
						player.GetWeapon()->SetOwner(-1);
						player.SetWeapon(nullptr);
					}
					
					player.SetWeapon(item);
					item->SetOwner(player.GetIndex());
				} else {
					if (player.HasItem()) {
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
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	
	for (Player &player : m_players) 
		player.Draw(win);
	
	for (Item *item : m_items)
		item->Draw(win);
	
	m_world.Draw(win);
	win.display();
}

void Match::UpdatePlayer(Player &player) {
	sf::Sprite p_sprite = player.GetSprite();
	
	int coll_index = m_world.CollidesWith(p_sprite);
	while (coll_index != -1 && player.GetSpeed().y != player.GetJumpSpeed()) {
		sf::Vector2<double> vec = m_world.GetResponse(p_sprite, coll_index);
		player.ApplyResponse(vec);
		
		if (coll_index == m_world.GetBaseIndex(0) && player.GetIndex() == 0)
			std::cout << "Player 0 is at home base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(1) && player.GetIndex() == 0)
			std::cout << "Player 0 is at enemy base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(1) && player.GetIndex() == 1)
			std::cout << "Player 1 is at home base!" << std::endl;
		else if (coll_index == m_world.GetBaseIndex(0) && player.GetIndex() == 1)
			std::cout << "Player 1 is at enemy base!" << std::endl;
		
		coll_index = m_world.CollidesWith(p_sprite, coll_index+1);
	}
	
	player.ApplyGravity(m_world.GetGravity());
	player.Update();
}

void Match::UpdateItem(Item *item) {
	sf::Sprite i_sprite = item->GetSprite();
	
	int coll_index = m_world.CollidesWith(i_sprite);
	while (coll_index != -1) {
		sf::Vector2<double> vec = m_world.GetResponse(i_sprite, coll_index);
		item->ApplyResponse(vec);
		coll_index = m_world.CollidesWith(i_sprite, coll_index+1);
	}
	
	if (item->Owner() != -1) 
		item->SetSpeed( {0,0} ); // reset the speed if item has an owner
	
	item->ApplyGravity(m_world.GetGravity());
	item->Update();
}

Match::~Match() {
	for (size_t i=0; i<m_items.size(); ++i) 
		delete m_items[i];
}
