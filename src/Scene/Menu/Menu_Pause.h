#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H
#include "Menu.h"
#include "../../Graphics/Camera.h"
#include <SFML/Graphics/RectangleShape.hpp>
class Menu_Pause : public Menu {
public:
	Menu_Pause(float width, float height,bool* pause,Camera* c);
	void ProcessEvent (sf::Event & e, Game & g)override;
	void Update (Game & g)override;
	void Render (DrawingEnviroment& drawEnv)override;
	void Close();
protected:
private:
	void Select(Game& g)override;
	void Relocate(sf::RenderWindow & win);
	
	bool* m_pause;
	Camera* m_c;
	sf::Vector2f m_pos, winsize;
	std::vector<sf::Vector2f> m_auxpos;
	sf::RectangleShape m_filter;

};

#endif

