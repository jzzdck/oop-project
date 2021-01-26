#ifndef DRAWINGENVIROMENT_H
#define DRAWINGENVIROMENT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class DrawingEnviroment
{
public:
	DrawingEnviroment(sf::RenderWindow* win,unsigned layer_amount=4);
	void AddToLayer(sf::Drawable* obj,unsigned layer_index);
	void ClearWindow();
	void DrawAll();
private:
	sf::RenderWindow* m_window;
	unsigned m_layer_amount;
	std::vector<std::vector<sf::Drawable*>> m_layer_pointers;
};

#endif

