#ifndef CONTROLS_H
#define CONTROLS_H
#include <map>
#include <SFML/Window/Keyboard.hpp>

class Controls {
public:
	bool KeyState(std::string const& key_functionconst); // returns true if the key is pressed
	void BindKey(std::string const& key_function,sf::Keyboard::Key new_key); // checks if the key_function exist, if not, adds it (wont check if the new_key overlaps with other key_function)
	sf::Keyboard::Key StringToKey(std::string const& str_key);
	sf::Keyboard::Key GetKey(std::string const& key_function);
	
	sf::Keyboard::Key operator<(std::string const& str_key); ///shortcut to string to key
	sf::Keyboard::Key operator<=(std::string const& key_function);///equivalent to m_keys[key_function]
	bool operator[](std::string const& key_function);
	Controls();
private:
	std::map<std::string,sf::Keyboard::Key> m_keys;
	std::map<std::string,sf::Keyboard::Key> m_special_keys;
};

#endif

