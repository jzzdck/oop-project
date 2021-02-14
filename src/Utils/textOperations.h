#ifndef TEXTOPERATIONS_H
#define TEXTOPERATIONS_H
#include <vector>
#include <string>
#include <SFML/Graphics/Text.hpp>

namespace utils {
	void replaceOption(int previous, int next, const std::vector<std::string> &options, sf::Text &to_replace);
	void replaceNumber(int new_number, sf::Text &to_replace, size_t start_pos = 0);
	void center(sf::Text &to_center, const sf::Vector2f &winsize);
}

#endif

