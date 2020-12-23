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
	PosSlideByColor(0);
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
		if((current_option>0)
		and(current_option<4)
		and(m_sliders[current_option-1].isAtLimit(0)))
			m_sliders[current_option-1].Move(0);
	}
	if(m_input["go_right"])
	{
		if((current_option>0)
		and(current_option<4)
		and(m_sliders[current_option-1].isAtLimit(1)))
			m_sliders[current_option-1].Move(1);
	}
	Move_Option_Down();
	Move_Option_Up();
}

void Menu_Color::Draw (sf::RenderWindow & win) 
{
	win.clear({0, 0, 0});
	CopyColorFromPlayer(0);//cambiamos el color del titulo al  del jugador
	HighlightCurrentOption();
	
	for(size_t i=m_texts.size()-3;i<m_texts.size();++i)
		CopyDistance(i,i-(m_texts.size()-3));
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
	PosSlideByColor(m_player_selected);
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
void Menu_Color::PosSlideByColor(bool const player)
{
	utils::HSV color;
	if(!player)
		color=utils::MakeHSV(m_cp0);
	else
		color=utils::MakeHSV(m_cp1);
	float x=color.GetHue()/360.f;
	float y=color.GetSat()/100.f;
	float z=color.GetVal()/100.f;
	m_sliders[0].JumpToPorcentage(x);
	m_sliders[1].JumpToPorcentage(y);
	m_sliders[2].JumpToPorcentage(z);	
}
