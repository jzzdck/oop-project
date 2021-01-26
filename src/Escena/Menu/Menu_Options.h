#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H
#include "Menu.h"

class Menu_Options:public Menu 
{
public:
	Menu_Options(float width,float height);
	
	void ProcessEvent(sf::Event& e,Game& g)override;
	void Update (Game & g)override;
	void Draw (DrawingEnviroment& drawEnv)override;
	
private:
	void Select(Game& g)override;
};

#endif

