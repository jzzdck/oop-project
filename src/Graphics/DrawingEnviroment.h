#ifndef DRAWINGENVIROMENT_H
#define DRAWINGENVIROMENT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class DrawingEnviroment
{
public:
	DrawingEnviroment(sf::RenderWindow* win,unsigned layer_amount);
	void AddToLayer(sf::Drawable* obj,unsigned layer_index);
	void ClearWindow(sf::Color c=sf::Color::Black);
	void DrawAll();
	sf::RenderWindow* getWin();///temporal function, it will probably deleted in the future
private:
	sf::RenderWindow* m_window;
	std::vector<std::vector<sf::Drawable*>> m_layer_pointers;
};

#endif

