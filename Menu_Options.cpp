#include "Menu_Options.h"
#include "Game.h"
#include "Menu_Color.h"
#include "phutils.h"

Menu_Options::Menu_Options(float width,float height):Menu(width,height,"options") 
{
}

void Menu_Options::ProcessEvent(sf::Event& e,Game& g)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if(e.key.code==sf::Keyboard::Escape)
			g.SetScene(new Menu_Principal(win_width, win_height));
		if(e.key.code==m_input<="select")
			Select(g);
	}	
}

void Menu_Options::Update (Game & g) 
{
	
	Move_Option_Down();
	Move_Option_Up();
}

void Menu_Options::Draw (sf::RenderWindow & win) 
{
	win.clear({0, 0, 0});
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
	win.display();
}

void Menu_Options::Select(Game& g)
{
	switch(current_option)
	{
	case 0:
		g.SetScene(new Menu_Color(win_width,win_height));
		break;
	case 1:
		//controls menu
		break; 
	case 2:
		g.SetScene(new Menu_Principal(win_width,win_height));
		break;
	}	
}
