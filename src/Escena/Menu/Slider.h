#ifndef SLIDER_H
#define SLIDER_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Menu.h"
class Menu::Slider
{
public:
	Slider();
	void Move(bool const direction);
	void JumpToPorcentage(float const value);
	float getPorcentualDistance();//returns the % of the distance beteween MinPos and MaxPos
	int getDistance();
	bool isAtLimit(bool const right_limit);
	
	void setLimits(float const MinPos,float MaxPos);
	void setLimits(sf::Vector2f const min_max);
	void setSpeed(sf::Vector2f const vel);
	void setSpeed(float const vel);
	void setColor(sf::Color const c);
	void setSize(sf::Vector2f const s);
	void setPosition(sf::Vector2f const p);
	void setTopValue(int const max_value);
	
	const sf::RectangleShape getRect()const;//shoud be only used  to draw the slider in screen
private:
	int m_TopValue;
	float m_MinPos,m_MaxPos;
	sf::Vector2f m_speed;
	sf::Color m_color;
	sf::RectangleShape m_r;
};
#endif

