#include "Plataform_static.h"
#include "../../../Utils/phutils.h"

Plataform_static::Plataform_static(std::string key):Plataform(key) 
{
}

void Plataform_static::LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  ) 
{


	sf::Vector2f dim = { win_width * stof(s_aux[m_key+"w"]), win_height * stof(s_aux[m_key+"h"]) };
	sf::Vector2f pos = { win_width * stof(s_aux[m_key+"x"]), win_height * stof(s_aux[m_key+"y"]) };
	
	sf::RectangleShape rect_aux(dim);
	rect_aux.setPosition(pos);
	sf::Color c=utils::getColor(s_aux["color"]);
	if (s_aux[m_key+"is-base0"] == "YES") {
		m_base=true;
		m_player=false;
		c=utils::loadPlayerColor(0);
	} else if (s_aux[m_key+"is-base1"] == "YES") {
		m_base=true;
		m_player=true;
		c=utils::loadPlayerColor(1);
	}
	rect_aux.setFillColor(c);
	this->setRect(rect_aux);
	
}
void Plataform_static::Move(){}
void Plataform_static::Update(){}
