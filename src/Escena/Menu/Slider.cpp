#include "Slider.h"
#include <SFML/Graphics/Rect.hpp>

Slider::Slider()
{
	
}

void Slider::Move(bool const direction)
{
	if(direction)
		m_r.move(m_speed.x,m_speed.y);
	else
		m_r.move(-m_speed.x,m_speed.y);
}

int Slider::getDistance()
{
	return getPorcentualDistance()*m_TopValue;
}
float Slider::getPorcentualDistance()
{
	sf::Rect<float> l=m_r.getGlobalBounds();
	return (l.left-m_MinPos)/(m_MaxPos-l.width-m_MinPos);
}
void Slider::JumpToPorcentage(float const value)
{
	sf::Rect<float> l=m_r.getGlobalBounds();
	float pos=value*(m_MaxPos-l.width-m_MinPos)+m_MinPos;
	m_r.setPosition(pos,l.top);
}
void Slider::setLimits(sf::Vector2f const min_max)
{
	m_MinPos=min_max.x;
	m_MaxPos=min_max.y;
}
void Slider::setLimits(float const MinPos,float const MaxPos)
{
	m_MinPos=MinPos;
	m_MaxPos=MaxPos;
}
bool Slider::isAtLimit(bool const right_limit)
{
	sf::Rect<float> dim=m_r.getGlobalBounds();
	if(right_limit)
		return ((dim.left+dim.width)<m_MaxPos);
	else
		return (dim.left>m_MinPos);
}

void Slider::setSpeed(sf::Vector2f const vel)
{
	m_speed=vel;
}
void Slider::setSpeed(float const vel)
{
	m_speed={vel,0};
}
void Slider::setColor(sf::Color const c)
{
	m_color=c;
}
void Slider::setSize(sf::Vector2f const s)
{
	m_r.setSize(s);
}
void Slider::setPosition(sf::Vector2f const p)
{
	m_r.setPosition(p);
}
void Slider::setTopValue(int const max_value)
{
	m_TopValue=max_value;
}
const sf::RectangleShape Slider::getRect()const
{
	return m_r;
}
