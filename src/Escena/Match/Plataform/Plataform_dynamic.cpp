#include "Plataform_dynamic.h"
#include "../../../Utils/phutils.h"
#include <sstream>

Plataform_dynamic::Plataform_dynamic(std::string key):Plataform(key) {
	
}

void Plataform_dynamic::LoadData (FileManager const& s_aux,float const& win_width,float const& win_height) 
{
	sf::Vector2f dim = { win_width * stof(s_aux[m_key+"w"]), win_height * stof(s_aux[m_key+"h"]) };
	sf::Vector2f pos = { win_width * stof(s_aux[m_key+"x"]), win_height * stof(s_aux[m_key+"y"]) };
	
	m_start=pos;
	m_end={ win_width * stof(s_aux[m_key+"x-end"]), win_height * stof(s_aux[m_key+"y-end"]) };
	
	sf::RectangleShape rect_aux(dim);
	rect_aux.setPosition(pos);
	sf::Color c=utils::getColor(s_aux["color"]);
	rect_aux.setFillColor(c);
	
	std::stringstream ss;
	ss<<s_aux[m_key+"linear-speed"];
	int x,y;
	ss>>x>>y;
	this->setLSpeed(sf::Vector2f(x,y));
	this->setAngSpeed(stoi(s_aux[m_key+"angular-speed"]));
	
	
	this->setRect(rect_aux);
	
}
void Plataform_dynamic::Move ( ) 
{
	if(this->CheckLimits(0))
		InvertLSpeed(0);
	if(this->CheckLimits(1))
		InvertLSpeed(1);
	
	m_rec.move(m_linear_speed);
}

void Plataform_dynamic::Update ( ) 
{
	this->Move();
}
sf::Vector2f Plataform_dynamic::getLSpeed()const
{
	return m_linear_speed;
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
		answ=(r.left>m_start.x)or(r.left<m_end.x);
	else
		answ=(r.top>m_start.y)or(r.top<m_end.y);
	return answ;
}
void Plataform_dynamic::InvertLSpeed(bool const& axis)
{
	if(!axis)
		m_linear_speed={-m_linear_speed.x,m_linear_speed.y};
	else
		m_linear_speed={m_linear_speed.x,-m_linear_speed.y};
}
