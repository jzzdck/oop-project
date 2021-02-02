#include "Menu_Pause.h"
#include "../../Game.h"
#include <SFML/Window/Event.hpp>
#include "Menu_Principal.h"
#include "../../Utils/generalUtils.h"

Menu_Pause::Menu_Pause(float width, float height,bool* pause,Camera* c):
	Menu(width,height,"pause"),
	m_pause(pause),m_c(c),m_filter({win_width*2.f, win_height*2.f})
{
	for(size_t i=0;i<m_texts.size();i++) 
	{
		m_auxpos.push_back(m_texts[i].getPosition());
	}
	m_filter.setOrigin(utils::getCenter(m_filter.getLocalBounds()));
	m_filter.setPosition(-win_width/2.f, -win_height/2.f);
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
	switch(e.type)
	{
	case sf::Event::KeyPressed:
		if(e.key.code==sf::Keyboard::P)
		{
			*m_pause=!*(m_pause);
			return;
		}
		if(e.key.code==m_input<="go_up")
		{
		   Move_Option_Up();
		   return;
		}
		if(e.key.code==m_input<="go_down")
		{
		   Move_Option_Down();
			return;
		}
		if(e.key.code==m_input<="select")
		{	
		   Select(g);
		   return;
		}
	default:
		
		break;
	}

}
void Menu_Pause::Update (Game & g)
{
	HighlightCurrentOption();
}

void Menu_Pause::Render (DrawingEnviroment& drawEnv) 
{
	Relocate(*drawEnv.getWin());
	
	for(auto &text : m_texts)
		drawEnv.AddToLayer(&text,1);
	drawEnv.AddToLayer(&m_filter,0);
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
		sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_auxpos[i]));
		m_texts[i].setPosition(pos);
		m_texts[i].setScale(0.8*zoom_level,0.8*zoom_level);
	}
	m_filter.setPosition(win.mapPixelToCoords(sf::Vector2i(-win_width/2.f, -win_height/2.f)));
	m_filter.setScale(1.5*zoom_level,1.5*zoom_level);
}