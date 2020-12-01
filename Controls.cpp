#include "Controls.h"
#include <map>
using namespace std;

Controls::Controls()
{
	
}

bool Controls::KeyState(string const& key)
{
	return sf::Keyboard::isKeyPressed(m_keys[key]);
}
void Controls::BindKey(string const& function_name,sf::Keyboard::Key new_key)
{
	map<string,sf::Keyboard::Key>::iterator pos=m_keys.find(function_name);
	if(pos==m_keys.end())
	{
		m_keys.insert({function_name,new_key});
	}
	else
	{
		m_keys[function_name]=new_key;
	}
}
