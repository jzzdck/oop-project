#include "World.h"
#include <string>
#include <sstream>

World::World(float wdt, float hgt, float gravity) : 
	win_width(wdt), win_height(hgt), m_gravity(gravity)
{
	LoadMap();
}

void World::LoadMap ( ) {
	int r, g, b;
	std::stringstream ss;
	Settings s("world.conf", "groundRects");
	m_platforms.resize(stoi(s["size"]));
	
	ss << s["color"];
	ss >> r >> g >> b;
	for (size_t i=0; i<m_platforms.size(); ++i) { 
		std::string key = "rect" + std::to_string(i) + "-"; //recti-w, recti-h, etc
		sf::RectangleShape aux(sf::Vector2f( win_width  * stof( s[key+"w"] ), 
											 win_height * stof( s[key+"h"] ) ));
		
		aux.setFillColor(sf::Color(r, g, b));
		aux.setPosition(sf::Vector2f( win_width  * stof( s[key+"x"] ), 
									  win_height * stof( s[key+"y"] ) ));
		
		m_platforms[i] = aux;
	}
}

int World::FloorCollision(sf::Sprite &entity) {
	auto entity_g = entity.getGlobalBounds();
	
	for (const auto &rect : m_platforms) {
		auto rect_g = rect.getGlobalBounds();
		auto entity_right = entity_g.left + entity_g.width;
		auto rect_right = rect_g.left + rect_g.width;
		
		if (rect_g.intersects(entity_g) &&
			rect_g.left < entity_right && 
			entity_g.left < rect_right) 
		{
			// floor collision
			if (rect_g.top+2 > entity_g.top + entity_g.height) 
				return -1;
			
			// ceiling collision
			if (rect_g.top+rect_g.height >= entity_g.top) 
				return 1;
		}
	}
	
	return 0;
}

int World::WallCollision(sf::Sprite &entity) {
	auto entity_g = entity.getGlobalBounds();
	
	for (const auto &rect : m_platforms) {
		auto rect_g = rect.getGlobalBounds();
		auto entity_bottom = entity_g.top + entity_g.height;
		auto rect_bottom = rect_g.top + rect_g.height;
		
		if (rect_g.intersects(entity_g) &&
			rect_g.top < entity_bottom && 
			entity_g.top < rect_bottom) 
		{
			// right wall collision
			// -10 para darle margen de error (si no siempre detecta esta)
			if (rect_g.left + rect_g.width - 10 > entity_g.left) 
				return -1;
			
			// left wall collision
			if (rect_g.left <= entity_g.left + entity_g.width)
				return 1;
		}
	}
	
	return 0;
}

void World::Draw (sf::RenderWindow & win) {
	for (const auto &rectangle : m_platforms)
		win.draw(rectangle);
}

