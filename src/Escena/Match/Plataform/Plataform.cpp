#include "Plataform.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Plataform::Plataform(std::string const& key):m_key(key),
	m_base(false),m_player(false)
{

}
void Plataform::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(m_rec);
}


sf::Rect<float> Plataform::getGlobalBounds()const
{
	return m_rec.getGlobalBounds();
}


void Plataform::setColor(sf::Color const& c)
{
	m_rec.setFillColor(c);
}
int Plataform::isBase()const
{
	if(!m_base)return -1;
	else return int(m_player);
}

void Plataform::setRect(sf::RectangleShape& r)
{
	m_rec=r;
}
void Plataform::setPos(sf::Vector2f pos)
{
	m_rec.setPosition(pos);
}
