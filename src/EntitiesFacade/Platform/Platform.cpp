#include "Platform.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Platform::Platform(std::string const& key):m_key(key),
	m_base(false),m_player(false)
{

}
void Platform::Render(DrawingEnviroment& drawEnv)
{
	drawEnv.AddToLayer(this,4);
}

int Platform::isBase()const
{
	if(!m_base)return -1;
	else return int(m_player);
}
