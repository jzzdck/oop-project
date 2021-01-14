#include "generalUtils.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../FileManager.h"

namespace utils {
	void flipTexture(float direction, float scale, sf::Sprite & to_turn) {
		to_turn.setScale(direction*scale, scale);
		if (direction == -1.f) 
			to_turn.setOrigin(to_turn.getLocalBounds().width, 0);
		else
			to_turn.setOrigin(0, 0);
	}
	
	sf::Vector2f getCenter(const sf::Rect<float> & of_this) 
	{
		float x_center = of_this.left+of_this.width/2.f;
		float y_center = of_this.top+of_this.height/2.f;
		return { x_center, y_center };
	}
	
	sf::Color getColor(std::string rgb)
	{
		int r, g, b;
		std::stringstream ss;
		
		ss << rgb;
		ss >> r >> g >> b;
		
		return sf::Color(r, g, b);
	}
	
	std::string getColorString(sf::Color rgb)
	{
		std::stringstream ss;
		ss<<std::to_string(rgb.r)<<" "<<std::to_string(rgb.g)<<" "<<std::to_string(rgb.b);
		return ss.str();
	}
	
	sf::Color loadPlayerColor(int player_index)
	{
		FileManager s("textures.conf","player");
		return utils::getColor(s["color-p"+std::to_string(player_index)]);
	}
	
	float randf() { return rand()%1001 / 1000.f; }
	
	bool wasPressed(bool &prev, bool act) {
		if (prev != act) {
			prev = !prev;
			return prev;
		}
		
		return false;
	}
}


