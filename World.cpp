#include "World.h"
#include "Entity.h"
#include <iostream>

int World::FloorCollision(sf::Sprite &entity) {
	auto entity_g = entity.getGlobalBounds();
	auto entity_l = entity.getLocalBounds();
	
	for (const auto &rect : m_platforms) {
		auto rect_g = rect.getGlobalBounds();
		auto rect_l = rect.getLocalBounds();
		
		auto entity_right = entity_g.left + entity_l.width;
		auto rect_right = rect_g.left + rect_l.width;
		
		if (rect_g.intersects(entity_g) &&
			rect_g.left <= entity_right && 
			entity_l.left <= rect_right) 
		{
			// floor collision
			if (rect_g.top >= entity_g.top + entity_l.height) 
				return 1;
			
			// ceiling collision
			if (rect_g.top+rect_l.height >= entity_g.top) 
				return 2;
		}
	}
	
	return 0;
}

int World::WallCollision(sf::Sprite &entity) {
	auto entity_g = entity.getGlobalBounds();
	auto entity_l = entity.getLocalBounds();
	
	for (const auto &rect : m_platforms) {
		auto rect_g = rect.getGlobalBounds();
		auto rect_l = rect.getLocalBounds();
		
		auto entity_bottom = entity_g.top + entity_l.height;
		auto rect_bottom = rect_g.top + rect_l.height;
		
		if (rect_g.intersects(entity_g) &&
			rect_g.top < entity_bottom && 
			entity_l.top < rect_bottom) 
		{
			// left wall collision
			if (rect_g.left <= entity_g.left + entity_l.width)
				return 1;
			
			// right wall collision
			if (rect_g.left + rect_l.width >= entity_g.left) 
				return -1;

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
	sf::RectangleShape rectangle(sf::Vector2f(win_width, win_height/2));
	rectangle.setFillColor({113, 189, 83});
	rectangle.setPosition(sf::Vector2f(0, win_height/2));
	
	sf::RectangleShape rectangle2(sf::Vector2f(win_width*0.2, 20));
	rectangle2.setFillColor({113, 189, 83});
	rectangle2.setPosition(sf::Vector2f(win_width/4, win_height/2 - win_height*0.1));
	
	m_platforms.push_back(rectangle);
	m_platforms.push_back(rectangle2);
}

