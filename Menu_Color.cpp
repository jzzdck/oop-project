#include "Menu_Color.h"
#include "Game.h"
#include "Menu_Options.h"
#include <cmath>

Menu_Color::Menu_Color(float width,float height):
	Menu(width,height,"color-options"),
	m_player_selected(false)
{
	LoadFigures();
	LoadSliders();
	///guardamos el color de los jugadores
	m_cp0 = utils::loadPlayerColor(0);
	m_cp1 = utils::loadPlayerColor(1);
}

void Menu_Color::Update (Game & g) 
{
	if(utils::wasPressed(charge_select, m_input["select"]))
	{
		if(charge_select)
		{
			switch (current_option) 
			{
			case 0:
				ChangePlayer();
				break;
			case 4:
				g.SetScene(new Menu_Options(win_width,win_height));
				break;
			}
		}
	}

	if(m_input["go_left"])
	{
		switch(current_option)
		{
		case 1:
			if(m_sliders[0].isAtLimit(0))m_sliders[0].Move(0);
			break;
		case 2:
			if(m_sliders[1].isAtLimit(0))m_sliders[1].Move(0);
			break;
		case 3:
			if(m_sliders[2].isAtLimit(0))m_sliders[2].Move(0);
			break;
		}
	}
	if(m_input["go_right"])
	{
		switch(current_option)
		{
		case 1:
			if(m_sliders[0].isAtLimit(1))m_sliders[0].Move(1);
			break;
		case 2:
			if(m_sliders[1].isAtLimit(1))m_sliders[1].Move(1);
			break;
		case 3:
			if(m_sliders[2].isAtLimit(1))m_sliders[2].Move(1);
			break;
		}
	}
	Move_Option_Down();
	Move_Option_Up();
}

void Menu_Color::Draw (sf::RenderWindow & win) 
{
	win.clear({0, 0, 0});
	CopyColorFromPlayer(0);//cambiamos el color del titulo al  del jugador
	for(size_t i=6;i<m_texts.size();++i)
	{
		CopyDistance(i,i-6);
	}
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
	for (const auto &rectangle : m_rectangles)
		win.draw(rectangle);
	for(const auto &slider:m_sliders)
		win.draw(slider.getRect());
	win.display();
}

void Menu_Color::ChangePlayer()
{
	m_player_selected=!m_player_selected;
	std::string aux;
	aux=m_texts[1].getString();//usamos =1 porque ahi esta el texto de player
	aux.resize(aux.size()-1);//le sacomos ya sea el 1 o 2
	aux+=std::to_string(int(m_player_selected)+1);
	m_texts[1].setString(aux);
}

void Menu_Color::CopyColorFromPlayer(unsigned const& text_position)
{
	if(!m_player_selected)
		m_texts[text_position].setFillColor(m_cp0);
	else
		m_texts[text_position].setFillColor(m_cp1);
}

void Menu_Color::CopyDistance(unsigned const& text_index,unsigned const slider_index)
{
	m_texts[text_index].setString(std::to_string(m_sliders[slider_index].getDistance()));
}
