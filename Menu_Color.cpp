#include "Menu_Color.h"
#include "Game.h"
#include "Menu_Options.h"
#include <cmath>

Menu_Color::Menu_Color(float width,float height):
	Menu(width,height,"color-options"),
	m_player_selected(false)
{
	LoadSliders();
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
			case 4:
				g.SetScene(new Menu_Options(win_width,win_height));
				break;
			}
		}
	}
	if(Move_Option_Left())
	{
		switch(current_option)
		{
		case 1:
			if(!Collides(m_sliders[0],m_sliders[2]))
				Move_MySlider(2,0);
			break;
		case 2:
			if(!Collides(m_sliders[3],m_sliders[5]))
				Move_MySlider(5,0);
			break;
		case 3:
			if(!Collides(m_sliders[6],m_sliders[8]))
				Move_MySlider(8,0);
			break;
		}
	}
	if(Move_Option_Right())
	{
		switch(current_option)
		{
		case 1:
			if(!Collides(m_sliders[1],m_sliders[2]))
				Move_MySlider(2,1);
			break;
		case 2:
			if(!Collides(m_sliders[4],m_sliders[5]))
				Move_MySlider(5,1);
			break;
		case 3:
			if(!Collides(m_sliders[7],m_sliders[8]))
				Move_MySlider(8,1);
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
	CopyDistance(6,{0,2});
	CopyDistance(7,{3,5});
	CopyDistance(8,{6,8});
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
	for (const auto &rectangle : m_sliders)
		win.draw(rectangle);
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

void Menu_Color::CopyDistance(unsigned const& text_position,sf::Vector2i const slider_index)
{
	int distance;
	sf::Rect<float> fig1,fig2;
	fig1=m_sliders[slider_index.x].getGlobalBounds();
	fig2=m_sliders[slider_index.y].getGlobalBounds();
	distance=(fig2.left)-(fig1.left+fig1.width);
	//si son los sliders de saturacion o brightness dividimos por 3.6 asi va de una escala del 1 al 100
	//pq? porque el Hue(color) va de 0 a 360 y s,b van de 0 a 100
	if((slider_index.y==5)or(slider_index.y==8))distance/=3.6;
	m_texts[text_position].setString(std::to_string(distance));
}
bool Menu_Color::Collides(sf::RectangleShape& b1,sf::RectangleShape& b2)
{
	sf::Rect<float> fig1=b1.getGlobalBounds();
	sf::Rect<float> fig2=b2.getGlobalBounds();
	return fig1.intersects(fig2);
}
