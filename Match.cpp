#include "Match.h"
#include "Game.h"
#include <iostream>

Match::Match(float width, float height) :
	Escena(width, height), m_world(width, height, 0.7)
{
	m_players.emplace_back( Player(win_width*0.9, win_height*0.5 - 200, 0) );
	m_players.emplace_back( Player(win_width*0.15, win_height*0.5 - 200, 1) );
}

void Match::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		g.SetScene(new Menu(win_width, win_height));
	
	for (auto &player : m_players) {
		sf::Sprite p_sprite = player.GetSprite();
		player.Update();
		
		int coll_index = m_world.CollidesWith(p_sprite);
		while (coll_index != -1 && player.GetSpeed().y != player.GetJumpSpeed()) {
			sf::Vector2<double> vec = m_world.GetResponse(p_sprite, coll_index);
			player.ApplyResponse(vec);
			
			coll_index = m_world.CollidesWith(p_sprite, coll_index+1);
		}
		
		player.ApplyGravity(m_world.GetGravity());
	}
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	
	for (auto player : m_players) 
		player.Draw(win);
	m_world.Draw(win);
	
	win.display();
}

Match::~Match() {
	
}

