#include "Menu_Pause.h"
#include "../../Game.h"
#include <SFML/Window/Event.hpp>
#include "Menu_Principal.h"
#include "../../Utils/generalUtils.h"
#include "../../Utils/HSV.h"

Menu_Pause::Menu_Pause(float width, float height,bool* pause,Camera* c):
	Menu(width,height,"pause"),
	m_pause(pause),m_c(c),m_filter({win_width*2.f, win_height*2.f})
{
	for(size_t i=0;i<m_texts.size();i++) 
	{
		m_auxpos.push_back(m_texts[i].getPosition());
		m_texts[i].setFillColor(sf::Color::White);
		m_texts[i].setCharacterSize(50);
		m_texts[i].setOutlineThickness(4);
		m_texts[i].setOutlineColor(sf::Color::Black);
	}
	m_filter.setFillColor({0, 0, 0, 100});
}

void Menu_Pause::Select (Game & g)
{
	switch(current_option)
	{
	case 0:
		this->Close();
		break;
	case 1:
		g.SetScene(new Menu_Principal(win_width, win_height));
		break;
	}
}

void Menu_Pause::ProcessEvent (sf::Event & e, Game & g) 
{
	// only keypresses are important
	if (e.type != sf::Event::KeyPressed) return;
	
	if (e.key.code==sf::Keyboard::P)
		*m_pause=!*(m_pause);
	else StandardMenuInput(g, e.key.code);
}
void Menu_Pause::Update (Game & g)
{
	Menu_Pause::HighlightCurrentOption();
}

void Menu_Pause::Render (DrawingEnviroment& drawEnv) 
{
	Relocate(*drawEnv.getWin());
	drawEnv.AddToLayer(&m_filter,1);
	
	for(auto &text : m_texts)
		drawEnv.AddToLayer(&text,0);
}

void Menu_Pause::Close()
{
	*(m_pause)=false;
}
void Menu_Pause::Relocate(sf::RenderWindow & win)
{
	float zoom_level=m_c->GetZoom();
	for(size_t i=0;i<m_texts.size();i++) 
	{
		sf::Vector2i pos = sf::Vector2i(m_auxpos[i]);
		m_texts[i].setPosition(win.mapPixelToCoords(pos));
		m_texts[i].setScale(zoom_level,zoom_level);
	}
	
	m_filter.setPosition(win.mapPixelToCoords({0, 0}));
	m_filter.setScale(1.5*zoom_level,1.5*zoom_level);
}
void Menu_Pause::HighlightCurrentOption ( ) 
{
	for (size_t i=m_Noptions.x; i<=m_Noptions.y; ++i)
	{
		m_texts[i].setFillColor({150, 150, 150});
	}
	
	m_texts[m_Noptions.x+current_option].setFillColor(sf::Color::White);
}
