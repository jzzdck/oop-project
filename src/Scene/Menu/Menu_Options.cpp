#include "Menu_Options.h"
#include "Menu_Color.h"
#include "Menu_Principal.h"
#include "MapMenu/MapMenu.h"
#include <SFML/Window/Event.hpp>
#include "../../Game.h"

Menu_Options::Menu_Options(float width,float height):Menu(width,height,"options") 
{
}

void Menu_Options::ProcessEvent(sf::Event& e,Game& g)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if(e.key.code==sf::Keyboard::Escape)
			g.SetScene(new Menu_Principal(win_width, win_height));
		else StandardMenuInput(g, e.key.code);
	}	
}

void Menu_Options::Update (Game & g) 
{
	
	HighlightCurrentOption();
}

void Menu_Options::Render (DrawingEnviroment& drawEnv) 
{
	drawEnv.ClearWindow();
	for(auto& text:m_texts)
		drawEnv.AddToLayer(&text,0);
	drawEnv.DrawAll();
}

void Menu_Options::Select(Game& g)
{
	switch(current_option)
	{
	case 0:
		g.SetScene(new Menu_Color(win_width,win_height));
		break;
	case 1:
		g.SetScene(new MapMenu(win_width, win_height));
		break; 
	case 2:
		g.SetScene(new Menu_Principal(win_width,win_height));
		break;
	}	
}
