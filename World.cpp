#include "World.h"
#include "Entity.h"
#include <iostream>

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

World::World(float wdt, float hgt, float gravity) : 
	win_width(wdt), win_height(hgt), m_gravity(gravity)
{
	sf::RectangleShape rectangle(sf::Vector2f(win_width/4, win_height/2));
	rectangle.setFillColor({113, 189, 83});
	rectangle.setPosition(sf::Vector2f(0, win_height/2));
	
	sf::RectangleShape tangle(sf::Vector2f(win_width/2, win_height/2));
	tangle.setFillColor({113, 189, 83});
	tangle.setPosition(sf::Vector2f(win_width/4 + 200, win_height/2));
	
	sf::RectangleShape rectangle2(sf::Vector2f(win_width*0.1, 20));
	rectangle2.setFillColor({113, 189, 83});
	rectangle2.setPosition(sf::Vector2f(win_width/3.4, win_height*0.4));
	
	sf::RectangleShape rectangle3(sf::Vector2f(win_width*0.4, 100));
	rectangle3.setFillColor({113, 189, 83});
	rectangle3.setPosition(sf::Vector2f(win_width/2, win_height*0.1));
	
	m_platforms.push_back(rectangle);
	m_platforms.push_back(tangle);
	m_platforms.push_back(rectangle2);
	m_platforms.push_back(rectangle3);
}

