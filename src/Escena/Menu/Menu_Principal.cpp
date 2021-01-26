#include "Menu_Principal.h"
#include "Menu.h"
#include "Menu_Options.h"
#include "../../Game.h"
#include "../../Utils/generalUtils.h"
#include "../Match/Match.h"

Menu_Principal::Menu_Principal(float width,float height):Menu(width,height,"principal") 
{
	LoadHeadline();
}

void Menu_Principal::ProcessEvent(sf::Event& e,Game& g)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if(e.key.code==sf::Keyboard::Escape)
			g.Close();
		if(e.key.code==m_input<="go_up")
			Move_Option_Up();
		if(e.key.code==m_input<="go_down")
			Move_Option_Down();
		if(e.key.code==m_input<="select")
			Select(g);
	}
}
void Menu_Principal::Update (Game & g)
{
	RandomizeMyColor(1);//el texto de headlines esta en la pos 1
	HighlightCurrentOption();
}

void Menu_Principal::Draw (DrawingEnviroment& drawEnv)
{
	drawEnv.ClearWindow();
	for(auto& text: m_texts)
		drawEnv.AddToLayer(&text,0);
	drawEnv.DrawAll();
}
void Menu_Principal::LoadHeadline() {
	std::ifstream fin("res/headlines.txt");
	std::vector<std::string> headlines;
	
	std::string aux;
	while (getline(fin, aux)) 
		headlines.push_back(aux);
	fin.close();
	for(sf::Text &x:m_texts)
	{
		if(x.getString()=="HEADLINE")
		{
			x.setString(headlines[rand() % headlines.size()]+"!");
			x.setOrigin(utils::getCenter(x.getLocalBounds()));
			break;
		}
	}
}
void Menu_Principal::Select(Game& g)
{
	switch(current_option)
	{
	case 0:
		g.SetScene(new Match(win_width, win_height));
		break;
	case 1:
		g.SetScene(new Menu_Options(win_width, win_height));
		break; 
	case 2:
		g.Close();
		break;
	}
}
