#include "Menu_Options.h"
#include "Menu_Color.h"
#include "../../Game.h"
#include "Menu_Principal.h"

Menu_Options::Menu_Options(float width,float height):Menu(width,height,"options") 
{
}

void Menu_Options::ProcessEvent(sf::Event& e,Game& g)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if(e.key.code==sf::Keyboard::Escape)
			g.SetScene(new Menu_Principal(win_width, win_height));
		if(e.key.code==m_input<="go_up")
			Move_Option_Up();
		if(e.key.code==m_input<="go_down")
			Move_Option_Down();
		if(e.key.code==m_input<="select")
			Select(g);
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
		//controls menu
		break; 
	case 2:
		g.SetScene(new Menu_Principal(win_width,win_height));
		break;
	}	
}
