#ifndef LOBBYMENU_H
#define LOBBYMENU_H
#include "Escena/Menu/Menu.h"
#include "MatchSettings.h"

class LobbyMenu : public Menu {
public:
	LobbyMenu();
	void ProcessEvent (sf::Event & e, Game & g) override;
	void Update (Game & g) override;
	void Draw (sf::RenderWindow & win) override;
protected:
	void Select (Game & g) override;
private:
	MatchSettings m_settings;
};

#endif

