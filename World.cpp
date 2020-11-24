#include "World.h"
#include "Entity.h"

bool World::CollidesWith(Entity &this_one) {
	auto entity_globals = this_one.GetGlobalBounds();
	
	for (auto &rect : m_platforms)
		if (rect.getGlobalBounds().intersects(entity_globals))
			return true;
	
	return false;
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
	
	m_platforms.push_back(rectangle);
}

