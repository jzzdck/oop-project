#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H
#include "Menu.h"

class Menu_Principal : public Menu{
public:
	Menu_Principal(float width,float height);
	void Update (Game & g)override;
	void Draw (sf::RenderWindow & win)override;
private:
	void LoadHeadline();
};

#endif

