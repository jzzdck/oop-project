#include "Menu_Color.h"
#include "Game.h"
#include "Menu_Options.h"

Menu_Color::Menu_Color(float width,float height):
	Menu(width,height,"color-options"),m_player_selected(false)  
{
	///guardamos el color de los jugadores
	m_cp0 = utils::loadPlayerColor(0);
	m_cp1 = utils::loadPlayerColor(1);
}

void Menu_Color::Update (Game & g) 
{
	if(Is_Selected())
	{
		if(charge_select)
		{
			switch (current_option) 
			{
			case 0:
				ChangePlayer();
				break;
			//	case 1:
			//		cambiar canal r
			//		break; 
			//	case 2:
			//		cambiar canal g
			//		break;
			//	case 3:
			//		cambiar canal b
			//		break;
			case 4:
				g.SetScene(new Menu_Options(win_width,win_height));
				break;
			}
		}
	}
	
	Move_Option_Down();
	Move_Option_Up();
}

void Menu_Color::Draw (sf::RenderWindow & win) 
{
	win.clear({0, 0, 0});
	CopyColorFromPlayer(0);//cambiamos el color del titulo al  del jugador
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
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
