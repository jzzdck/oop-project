#include "generalUtils.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <filesystem>
#include "FileManager.h"
#include <SFML/Graphics/Transformable.hpp>

namespace utils {
	void flipTexture(float direction, float scale, sf::Sprite & to_turn) {
		to_turn.setScale(direction*scale, scale);
		if (direction == -1.f) 
			to_turn.setOrigin(to_turn.getLocalBounds().width, 0);
		else
			to_turn.setOrigin(0, 0);
	}
	
	sf::Vector2f getCenter(const sf::Rect<float>& of_this) {
		float x_center = of_this.left+of_this.width/2.f;
		float y_center = of_this.top+of_this.height/2.f;
		return { x_center, y_center };
	}
	
	sf::Rect<float> getRectDim(std::string s){
		std::stringstream ss(s);
		sf::Rect<float> aux;
		ss>>aux.left>>aux.top>>aux.width>>aux.height;
		return aux;
		
	}
	
	sf::Vector2f getXY(std::string s) {
		std::stringstream ss(s);
		sf::Vector2f aux;
		ss>>aux.x>>aux.y;
		return aux;
	}
	
	sf::Color getColor(std::string rgb) {
		int r, g, b;
		std::stringstream ss;
		
		ss << rgb;
		ss >> r >> g >> b;
		
		return sf::Color(r, g, b);
	}
	
	std::string getColorString(sf::Color rgb) {
		std::stringstream ss;
		ss<<std::to_string(rgb.r)<<" "<<std::to_string(rgb.g)<<" "<<std::to_string(rgb.b);
		return ss.str();
	}
	
	sf::Color loadPlayerColor(int player_index) {
		FileManager s("textures.conf","player");
		return utils::getColor(s["color-p"+std::to_string(player_index)]);
	}
	
	float randf() { 
		return rand()%1001 / 1000.f; 
	}
	
	std::string rectDimsToString(const sf::Rect<float> & to_convert) {
		std::stringstream ss;
		
		ss << to_convert.left << " " << to_convert.top << " " << to_convert.width << " " << to_convert.height;
		
		return ss.str();
	}
	
	std::string getRandomMap( ) {
		std::vector<std::string> all_maps = getMapnames();
		return all_maps.at(rand()%(all_maps.size()));
	}
	
	std::vector<std::string> getMapnames( ) {
		std::vector<std::string> mapnames;
		
		std::string path("../res/configuration-files/maps/");
		for (auto &p : std::filesystem::directory_iterator(path))
			if (p.path().extension() == ".conf")
				mapnames.push_back(p.path().stem());
		
		return mapnames;
	}

	int wrap(int &to_wrap, int range) {
		if (to_wrap == -1)
			to_wrap = range - 1;
		else
			to_wrap %= range;
		
		return to_wrap;
	}
	
	sf::Vector2f getFixedPos(sf::RenderWindow * win, const sf::Vector2f & abpos, const sf::Vector2f & revpos) {
		sf::Vector2u winsize = win->getSize();
		sf::Vector2f abs(winsize.x * abpos.x, winsize.y * abpos.y);
		sf::Vector2f pos(winsize.x * revpos.x, winsize.y * revpos.y);
		return win->mapPixelToCoords(sf::Vector2i(pos + abs));
	}
}

