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
	m_camera(width, height),
	m_pmenu(width,height,&m_pause)
{
	m_camera.SetPlayers(m_entities.GetPlayers());
	m_gamehud.SetPlayers(m_entities.GetPlayers());
}

void Match::ProcessEvent(sf::Event& e, Game& g) 
{
	switch(e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape)
		{
			g.SetScene(new Menu_Principal(win_width, win_height));
			return;
		}
		if(e.key.code==sf::Keyboard::P)
		{
			m_pause=!m_pause;
			return;
		}
	default:
		if(m_pause)
			m_pmenu.ProcessEvent(e,g);
		else
			m_entities.ProcessPlayersEvents(e, g);
		break;
	}
	
}

void Match::Update (Game& g) {
	if (m_pause)
	{
		m_pmenu.Update(g);
		return;
	}
	m_camera.Update();
	m_entities.Update();
	m_gamehud.Update();
}

void Match::Draw (sf::RenderWindow & win)
{
	win.clear({158, 207, 222});
	m_camera.SetToWindow(win);
	m_entities.Draw(win);
	m_gamehud.Draw(win, m_camera.GetZoom());
	
	if (m_pause)
		m_pmenu.Draw(win);
	
	win.display();
}

Match::~Match() {
	
}

