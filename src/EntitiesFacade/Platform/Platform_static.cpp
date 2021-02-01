#include "Platform_static.h"
#include "../../Utils/generalUtils.h"

Platform_static::Platform_static(std::string key):Platform(key) 
{
}

void Platform_static::LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  ) 
{
	sf::Rect<float> dim=utils::getRectDim(s_aux[m_key+"dim"]);
	dim.left*=win_width;
	dim.top*=win_height;
	dim.width*=win_width;
	dim.height*=win_height;
	
	this->setSize({dim.width,dim.height});
	this->setPosition({dim.left,dim.top});
	
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
	this->setFillColor(c);
}
void Platform_static::Move(){}
void Platform_static::Update(){}
