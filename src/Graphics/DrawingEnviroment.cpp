#include "DrawingEnviroment.h"
#include <iostream>

DrawingEnviroment::DrawingEnviroment(sf::RenderWindow& win,unsigned layer_amount):
	m_window(win)
{
	m_layer_pointers.resize(layer_amount);
}
void DrawingEnviroment::ClearWindow()
{
	m_window.clear();
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
	for(size_t i=0;i<m_layer_pointers.size();i++) 
	{
		for(sf::Drawable* x:m_layer_pointers[i])
			m_window.draw(*x);
	}
}
