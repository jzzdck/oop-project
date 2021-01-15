#include "Plataform_dynamic.h"
#include "../../../Utils/generalUtils.h"
#include <sstream>
#include <cmath>
#include <iostream>

Plataform_dynamic::Plataform_dynamic(std::string key):Plataform(key) {
	
}

void Plataform_dynamic::LoadData (FileManager const& s_aux,float const& win_width,float const& win_height) 
{
	sf::Rect<float> dim=utils::getRectDim(s_aux[m_key+"dim"]);
	dim.left*=win_width;
	dim.top*=win_height;
	dim.width*=win_width;
	dim.height*=win_height;
	
	sf::RectangleShape rect_aux({dim.width,dim.height});
	rect_aux.setPosition({dim.left,dim.top});
	
	m_start={dim.left,dim.top};
	m_end=utils::getXY(s_aux[m_key+"xy-end"]);
	m_end.x*=win_width;
	m_end.y*=win_height;
	
	sf::Color c=utils::getColor(s_aux["color"]);
	rect_aux.setFillColor(c);
	
	this->setLSpeed(utils::getXY(s_aux[m_key+"linear-speed"]));
	this->setAngSpeed(stoi(s_aux[m_key+"angular-speed"]));
	this->setRect(rect_aux);
	
	m_radius=stof(s_aux[m_key+"radius"])*win_height;
	m_angle=0;
}
void Plataform_dynamic::Move ( ) 
{
	Rotate();
	m_rec.move(m_linear_speed + m_angular);
	
	if(this->CheckLimits(0))
		InvertLSpeed(0);
	if(this->CheckLimits(1))
		InvertLSpeed(1);
}

void Plataform_dynamic::Update ( ) 
{
	this->Move();
}

float Plataform_dynamic::getAngSpeed()const
{
	return m_angular_speed;
}

void Plataform_dynamic::setLSpeed(sf::Vector2f const& speed)
{
	m_linear_speed=speed;
}
void Plataform_dynamic::setAngSpeed(float const& speed)
{
	m_angular_speed=speed;
}

bool Plataform_dynamic::CheckLimits(bool const& axis)
{
	sf::Rect<float> r=this->getGlobalBounds();
	bool answ;
	if(!axis)
		answ=(r.left<m_start.x)or(r.left>m_end.x);
	else
		answ=(r.top>m_start.y)or(r.top<m_end.y);
	return answ;
}
void Plataform_dynamic::InvertLSpeed(bool const& axis)
{
	if(!axis)
		m_linear_speed.x *= -1.f;
	else
		m_linear_speed.y *= -1.f;
}
void Plataform_dynamic::InvertAngSpeed()
{
	m_angular_speed*=-1;
}
void Plataform_dynamic::Rotate()
{
	m_angle+=m_angular_speed;
	m_angular = {
		m_radius*std::cos(m_angle*3.14f), 
		m_radius*std::sin(m_angle*3.14f)
	};
}
	
