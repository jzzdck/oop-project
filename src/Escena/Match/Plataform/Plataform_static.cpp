#include "Plataform_static.h"
#include "../../../Utils/generalUtils.h"

Plataform_static::Plataform_static(std::string key):Plataform(key) 
{
}

void Plataform_static::LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  ) 
{
	sf::Rect<float> dim=utils::getRectDim(s_aux[m_key+"dim"]);
	dim.left*=win_width;
	dim.top*=win_height;
	dim.width*=win_width;
	dim.height*=win_height;
	
	sf::RectangleShape rect_aux({dim.width,dim.height});
	rect_aux.setPosition({dim.left,dim.top});
	
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
