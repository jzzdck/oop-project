#include "World.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../FileManager.h"
#include "../../Utils/phutils.h"
#include "Plataform/Plataform_static.h"
#include <vector>

World::World(float wdt, float hgt, float gravity, std::string map_name) : 
	win_width(wdt), win_height(hgt), m_gravity(gravity),
	m_map(map_name), m_base0(-1), m_base1(-1)
{
	LoadMap(map_name);
}

void World::LoadMap(std::string map_name) {
	FileManager s1("maps.conf", map_name+"-static");
	FileManager s2("maps.conf", map_name+"-dynamic");
	size_t size1=stoi(s1["size"]);
	for(size_t i=0;i<size1;++i)	
	{
		m_platforms.push_back(new Plataform_static("rect" + std::to_string(i) + "-"));
		m_platforms[i]->LoadData(s1,win_width,win_height);
		if(m_platforms[i]->isBase()!=-1)
		{
			if(m_platforms[i]->isBase()==0)
				m_base0=i;
			else
				m_base1=i;
		}
	}
	
	/*
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
	}*/
	
}

int World::CollidesWith(const sf::Sprite &entity, sf::Vector2f &response, int index) {
	if (index >= m_platforms.size()) return -1;
	
	sf::Rect<float> entity_g = entity.getGlobalBounds();
	for (size_t i=index; i<m_platforms.size(); ++i) {
		sf::Rect<float> intersection;
		sf::Rect<float> rect_g = m_platforms[i]->getGlobalBounds();
		if (entity_g.intersects(rect_g, intersection)) {
			sf::Vector2f dir;
			dir.y = rect_g.top  > entity_g.top  ? -1.f : 1.f;
			dir.x = rect_g.left > entity_g.left ? -1.f : 1.f;
			
			if (intersection.width < intersection.height)
				response = { dir.x*intersection.width, 0 };
			else
				response = { 0, dir.y*intersection.height };
			
			return i;
		}
	}

	return -1;
}

void World::Draw (sf::RenderWindow& win) {
	for (Plataform* &p: m_platforms)
		p->Draw(win);
}
World::~World()
{
	for(size_t i=0;i<m_platforms.size();i++) 
	{
		delete m_platforms[i];
	}
}
