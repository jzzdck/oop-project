#include "Match.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "../../Game.h"
#include "../../Entity/Player.h"
#include "../Menu/Menu_Principal.h"

Match::Match(float width, float height) :
	Escena(width, height), m_pause(false),
	m_entities(width, height, "MAIN"), 
	m_camera(width, height)
{
	m_camera.SetPlayers(m_entities.GetPlayers());
	m_gamehud.SetPlayers(m_entities.GetPlayers());
}

void Match::ProcessEvent(sf::Event& e, Game& g) 
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Escape)
			g.SetScene(new Menu_Principal(win_width, win_height));
		else if (e.key.code == sf::Keyboard::P)
			m_pause=!m_pause;
	}
}

void Match::Update (Game& g) {
	if (m_pause) { /* update pause */ return; }
	
	m_camera.Update();
	m_entities.Update();
	m_gamehud.Update();
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	m_camera.SetToWindow(win);
	m_entities.Draw(win);
	m_gamehud.Draw(win, m_camera.GetZoom());
	
	if (m_pause) { 
		/* draw pause */
		sf::RectangleShape s({win_width*2.f, win_height*2.f});
		s.setPosition(-win_width/2.f, -win_height/2.f);
		s.setFillColor({0, 0, 0, 100});
		win.draw(s); 
	}
	
	win.display();
}

Match::~Match() {
	
}

