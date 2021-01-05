#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H
#include "Menu.h"

class Menu_Principal : public Menu{
public:
	Menu_Principal(float width,float height);
	
	void ProcessEvent(sf::Event& e,Game& g)override;
	void Update (Game & g)override;
	void Draw (sf::RenderWindow & win)override;
	
private:
	void Select(Game& g)override;
	
	void LoadHeadline();
};

#endif

