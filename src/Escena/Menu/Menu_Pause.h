#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H
#include "Menu.h"

class Menu_Pause : public Menu {
public:
	Menu_Pause(float width, float height,bool* pause);
	void ProcessEvent (sf::Event & e, Game & g)override;
	void Update (Game & g)override;
	void Draw (sf::RenderWindow & win)override;
	void Close();
	void Fade(sf::RenderWindow & win);
protected:
	void Select (Game & g);
private:
	bool* m_pause;
};

#endif

