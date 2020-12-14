#include "Menu_Principal.h"
#include "Menu.h"
#include "Game.h"
#include "Menu_Options.h"

Menu_Principal::Menu_Principal(float width,float height):Menu(width,height,"principal") 
{
	LoadHeadline();
}

void Menu_Principal::Update (Game & g)
{
	if(Is_Selected()) 
	{
		if(charge_select) 
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
	}
	
	Move_Option_Down();
	Move_Option_Up();
}

void Menu_Principal::Draw (sf::RenderWindow & win)
{
	win.clear({0, 0, 0});
	RandomizeMyColor(1);//el texto de headlines esta en la pos 1
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
	win.display();
	
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
			///el siguiente codigo centra el texto
			sf::FloatRect text_rect = x.getLocalBounds();
			x.setOrigin(text_rect.left+text_rect.width/2, text_rect.top+text_rect.height/2 );
			break;
		}
	}
}
