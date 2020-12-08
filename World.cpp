#include "World.h"
#include <string>
#include <sstream>
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "phutils.h"

World::World(float wdt, float hgt, float gravity, std::string map_name) : 
	win_width(wdt), win_height(hgt), m_gravity(gravity),
	m_map(map_name), m_base0(-1), m_base1(-1)
{
	LoadMap(map_name);
}

void World::LoadMap(std::string map_name) {
	Settings s("maps.conf", map_name);
	m_platforms.resize(stoi(s["size"]));
	
	m_c = utils::getColor(s["color"]);
	for (size_t i=0; i<m_platforms.size(); ++i) {
		std::string key = "rect" + std::to_string(i) + "-"; //recti-w, recti-h, etc
		sf::Vector2f dim = { win_width * stof(s[key+"w"]), win_height * stof(s[key+"h"]) };
		sf::Vector2f pos = { win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]) };
		
		sf::RectangleShape aux(dim);
		aux.setPosition(pos);
		
		if (s[key+"is-base0"] == "YES") {
			m_base0 = i;
			aux.setFillColor(utils::loadPlayerColor(0));
		} else if (s[key+"is-base1"] == "YES") {
			m_base1 = i;
			aux.setFillColor(utils::loadPlayerColor(1));
		} else aux.setFillColor(m_c);
		
		m_platforms[i] = aux;
	}
}

sf::Vector2<double> World::GetResponse(const sf::Sprite &entity, int index) {
	sf::Rect<float> e = entity.getGlobalBounds();
	sf::Rect<float> r = m_platforms[index].getGlobalBounds();
	sf::Vector2f ec = utils::getCenter(e);
	sf::Vector2f rc = utils::getCenter(r);
	
	sf::Vector2<double> delta = { rc.x - ec.x, rc.y - ec.y };
	sf::Vector2<double> proj = { std::fabs(delta.x) - 0.5*(e.width  + r.width), 
								 std::fabs(delta.y) - 0.5*(e.height + r.height) };
	
	if (std::fabs(proj.x) < std::fabs(proj.y)) {
		proj.y = 0;
		if (delta.x < 0) proj.x *= -1;
	} else {
		proj.x = 0;
		if (delta.y < 0) proj.y *= -1;
	}
	
	return { proj.x, proj.y };
}

int World::CollidesWith(const sf::Sprite &entity, int index) {
	if (index >= m_platforms.size()) return -1;
	
	sf::Rect<float> entity_g = entity.getGlobalBounds();
	for (size_t i=index; i<m_platforms.size(); ++i)
		if (m_platforms[i].getGlobalBounds().intersects(entity_g))
			return i;

	return -1;
}

void World::Draw (sf::RenderWindow & win) {
	for (const auto &rectangle : m_platforms)
		win.draw(rectangle);
}

