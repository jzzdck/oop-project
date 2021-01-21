#include "Menu_Pause.h"
#include "../../Game.h"
#include <SFML/Window/Event.hpp>

Menu_Pause::Menu_Pause(float width, float height,bool* pause):
	Menu(width,height,"pause"),
	m_pause(pause)
{
	
}

void Menu_Pause::Select (Game & g)
{
	switch(current_option)
	{
	case 1:
		this->Close();
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

void Menu_Pause::Draw (sf::RenderWindow & win) 
{
	Fade(win);
	for(const auto &text : m_texts)
		win.draw(text);
}

void Menu_Pause::Close()
{
	*(m_pause)=false;
}
void Menu_Pause::Fade(sf::RenderWindow & win)
{
	sf::RectangleShape s({win_width*2.f, win_height*2.f});
	s.setPosition(-win_width/2.f, -win_height/2.f);
	s.setFillColor({0, 0, 0, 100});
	win.draw(s);	
}

