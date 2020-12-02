#include "Match.h"
#include "Game.h"
#include <iostream>

Match::Match(float width, float height) :
	Escena(width, height), m_world(width, height, 0.5)
{
	m_players.emplace_back( Player(win_width*0.9, win_height*0.5 - 200, 0) );
	m_players.emplace_back( Player(win_width*0.15, win_height*0.5 - 200, 1) );
}

void Match::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		g.SetScene(new Menu(win_width, win_height));
	
	for (auto &player : m_players) {
		player.Update();
		
		if (m_world.FloorCollision(player.GetSprite()))
			player.RespondFloorCollision();
		else 
			player.ApplyForce(0, m_world.GetGravity());
		
		int dir = m_world.WallCollision(player.GetSprite());
		if (dir) player.RespondWallCollision(dir);
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

