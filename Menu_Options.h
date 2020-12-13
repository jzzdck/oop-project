#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H
#include "Menu.h"

class Menu_Options:public Menu 
{
public:
	Menu_Options(float width,float height);
	void Update (Game & g)override;
	void Draw (sf::RenderWindow & win)override;
private:
};

#endif

