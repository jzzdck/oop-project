#include "DrawingEnviroment.h"
#include <iostream>

DrawingEnviroment::DrawingEnviroment(sf::RenderWindow* win,unsigned layer_amount):
	m_window(win), m_layer_amount(layer_amount)
{
	m_layer_pointers.resize(layer_amount);
}
void DrawingEnviroment::ClearWindow(sf::Color c)
{
	m_window->clear(c);
	for(size_t i=0;i<m_layer_pointers.size();i++)
	{
		m_layer_pointers[i].resize(0);
	}
}
void DrawingEnviroment::AddToLayer(sf::Drawable* obj,unsigned layer_index)
{
	if(layer_index>=m_layer_amount)
	{
		layer_index=m_layer_amount-1;
		std::cerr<<"\nLayer index greater than layer amount, asuming last layer\n";
	}
	m_layer_pointers[layer_index].push_back(obj);
}
void DrawingEnviroment::DrawAll()
{
	for(auto it_vec=m_layer_pointers.rbegin();it_vec!=m_layer_pointers.rend();it_vec++)
		for(size_t j=0;j<it_vec->size();j++)
			m_window->draw(*(*it_vec)[j]);

	m_window->display();
}
sf::RenderWindow* DrawingEnviroment::getWin()
{
	return m_window;
}
