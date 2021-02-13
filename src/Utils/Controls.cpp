#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Controls.h"
using namespace std;

Controls::Controls()
{
	m_special_keys = {
		{"Left", sf::Keyboard::Key::Left}, {"Right", sf::Keyboard::Key::Right},
		{"Up", sf::Keyboard::Key::Up}, {"Down", sf::Keyboard::Key::Down},
		{"Numpad0", sf::Keyboard::Key::Numpad0},
		{"Numpad1", sf::Keyboard::Key::Numpad1},
		{"Numpad2", sf::Keyboard::Key::Numpad2},
		{"Numpad3", sf::Keyboard::Key::Numpad3},
		{"Numpad4", sf::Keyboard::Key::Numpad4},
		{"Numpad5", sf::Keyboard::Key::Numpad5},
		{"Numpad6", sf::Keyboard::Key::Numpad6},
		{"Numpad7", sf::Keyboard::Key::Numpad7},
		{"Numpad8", sf::Keyboard::Key::Numpad8},
		{"Numpad9", sf::Keyboard::Key::Numpad9},
		{"Space", sf::Keyboard::Key::Space}, 
		{"Enter", sf::Keyboard::Key::Enter},
		{"Add", sf::Keyboard::Key::Add}, 
		{"Subtract", sf::Keyboard::Key::Subtract},
		{"Multiply", sf::Keyboard::Key::Multiply}, 
		{"Divide", sf::Keyboard::Key::Divide}
	};
}

bool Controls::KeyState(string const& key_function)
{
	return sf::Keyboard::isKeyPressed(m_keys[key_function]);
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
sf::Keyboard::Key Controls::StringToKey(std::string const& str_key)
{
	
	if (str_key.size() == 1)
		return sf::Keyboard::Key(str_key[0] - 'A');
	
	auto it = m_special_keys.find(str_key);
	if (it != m_special_keys.end())
		return it->second;
	
	// si no es ninguna de estas, devuelve Unknown
	std::cerr<<str_key<<" is an unknown key";
	return sf::Keyboard::Key::Unknown ;
}
sf::Keyboard::Key Controls::operator<(std::string const& str_key)
{
	return StringToKey(str_key);
}
sf::Keyboard::Key Controls::operator<=(std::string const& key_function)
{
	return m_keys[key_function];
}
bool Controls::operator[](std::string const& key_function){
	return KeyState(key_function);
}

sf::Keyboard::Key Controls::GetKey (std::string const& key_function) 
{
	return m_keys[key_function];
}

