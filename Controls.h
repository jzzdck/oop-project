#ifndef CONTROLS_H
#define CONTROLS_H
#include <map>
#include <SFML/Window/Keyboard.hpp>

class Controls {
public:
	Controls();
	bool KeyState(std::string const& key);//retunrs true if the key is pressed
	void BindKey(std::string const& key_function,sf::Keyboard::Key new_key);// checks if the key_function exist, if not, adds it (it will not check if the new_key overlaps with other key_function)
private:
	std::map<std::string,sf::Keyboard::Key> m_keys;
};

#endif

