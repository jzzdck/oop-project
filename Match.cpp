#include "Match.h"
#include "Game.h"

Match::Match(float width, float height) :
	Escena(width, height), m_world(width, height, 0.5)
{
	m_players.resize(2);
	m_players[0] = new Player(win_width*0.3, win_height/2 - 200, 0);
	m_players[1] = new Player(win_width*0.2, win_height/2 - 200, 1);
}

void Match::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		g.SetScene(new Menu(win_width, win_height));
	
	for (auto player : m_players)
		player->Update(m_world);
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	
	for (auto player : m_players) 
		player->Draw(win);
	m_world.Draw(win);
	
	win.display();
}

Match::~Match() {
	for (size_t i=0; i<m_players.size(); ++i) 
		delete m_players[i];
}

