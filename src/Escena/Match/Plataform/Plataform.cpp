#include "Plataform.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Plataform::Plataform(std::string const& key):m_key(key)
{

}
void Plataform::Draw(sf::RenderWindow& w)
{
	w.draw(m_rec);
}


sf::Rect<float> Plataform::getGlobalBounds()const
{
	return m_rec.getGlobalBounds();
}
sf::Vector2f Plataform::getSpeed()const
{
	return m_speed;
}
void Plataform::setSpeed(sf::Vector2f const& speed)
{
	m_speed=speed;
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
