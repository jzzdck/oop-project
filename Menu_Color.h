#ifndef MENU_COLOR_H
#define MENU_COLOR_H
#include "Menu.h"

class Menu_Color : public Menu {
public:
	Menu_Color(float width,float height);
	void Update (Game & g)override;
	void Draw (sf::RenderWindow & win)override;
private:
	void ChangePlayer();
	void CopyColorFromPlayer(unsigned const& text_position);
	void CopyDistance(unsigned const& text_index,unsigned const slider_index);
	
	void PosSlideByColor(bool const player);
	void UpdatePColor();
	void RandomizeSliders();
	void SaveColorChanges();
	
	bool m_player_selected;
	std::vector<sf::Color> m_cp;
	
};

#endif

