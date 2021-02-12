#include "TextOperations.h"
#include "Utils/generalUtils.h"

namespace utils {	
	void replaceOption(int previous, int next, const std::vector<std::string> & options, sf::Text & to_replace) {
		std::string str = to_replace.getString();
		std::string aux = options[previous];
		
		size_t pos = str.find(aux);
		if (pos != std::string::npos)
			str = str.replace(pos, aux.size(), options[next]);
		to_replace.setString(str);
	}
	
	void replaceNumber(int new_number, sf::Text & to_replace, size_t starting_pos) {
		std::string str = to_replace.getString();
		size_t b_pos = str.find_first_of("1234567890", starting_pos);
		size_t e_pos = str.find_first_not_of("1234567890", b_pos);
		if (b_pos != std::string::npos && e_pos != std::string::npos)
			str = str.replace(b_pos, e_pos-b_pos, std::to_string(new_number));
		to_replace.setString(str);
	}
	
	void center(sf::Text & to_center, const sf::Vector2f &winsize) {
		float prev_pos = to_center.getPosition().y, prev_origin = to_center.getOrigin().y;
		
		to_center.setOrigin(utils::getCenter(to_center.getLocalBounds()).x, prev_origin);
		to_center.setPosition(winsize.x*0.5f, prev_pos);
	}
}
