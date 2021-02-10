#include "Slider.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Slider::Slider()
{
	
}


void Slider::Move(bool const direction)
{
	if(direction)
		this->move(m_speed.x,m_speed.y);
	else
		this->move(-m_speed.x,m_speed.y);
}

int Slider::getDistance()
{
	return getPorcentualDistance()*m_TopValue;
}
float Slider::getPorcentualDistance()
{
	sf::Rect<float> l=this->getGlobalBounds();
	return (l.left-m_MinPos)/(m_MaxPos-l.width-m_MinPos);
}
void Slider::JumpToPorcentage(float const value)
{
	sf::Rect<float> l=this->getGlobalBounds();
	float pos=value*(m_MaxPos-l.width-m_MinPos)+m_MinPos;
	this->setPosition(pos,l.top);
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
	sf::Rect<float> dim=this->getGlobalBounds();
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
void Slider::setTopValue(int const max_value)
{
	m_TopValue=max_value;
}
