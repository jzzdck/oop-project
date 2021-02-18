#include "World.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../Utils/generalUtils.h"
#include "../Utils/CollisionUtil.h"

World::World(float wdt, float hgt, float gravity, std::string map_name) : 
	win_width(wdt), win_height(hgt), m_gravity(gravity),
	m_map(map_name), m_base0(-1), m_base1(-1)
{
	LoadMap(map_name);
}

void World::LoadMap(std::string map_name) {
	FileManager s1("/maps/" + map_name + ".conf", map_name+"-static");
	
	auto aux = utils::getXY(s1["bounds"]);
	float scale = std::stof(s1["scale"]);
	m_bounds = { 0, 0, aux.x*scale, aux.y*scale };

	size_t size1=stoi(s1["size"]);
	
	for(size_t i=0;i<size1;++i)	{
		std::string key = "rect" + std::to_string(i) + "-";
		m_platforms.push_back(Platform(key, s1, aux));
		if (m_platforms[i].IsBase()!=-1) {
			if (m_platforms[i].IsBase()==0)
				m_base0=i;
			else
				m_base1=i;
		}
	}
}

void World::Update() {
	for(Platform &platform : m_platforms)
		platform.Update();
}

void World::Render (DrawingEnviroment& drawEnv) {
	for (Platform &platform : m_platforms)
		platform.Render(drawEnv);
}

World::~World() {

}

int World::CollidesWith (Entity * entity, sf::Vector2f & response, int index) {
	if (index >= m_platforms.size()) return -1;
	
	utils::Box entity_box = {
		entity->GetBounds(), 
		entity->GetSpeed()
	};
	
	for (size_t i = index; i < m_platforms.size(); ++i) {
		utils::Box platform_box = {
			m_platforms[i].getGlobalBounds(), 
			m_platforms[i].GetSpeed()
		};
		
		sf::Rect<float> md = utils::minkowskiDifference(entity_box, platform_box);
		if (utils::minkowskiCollision(md)) {
			response = utils::getPenetration(md);
			if (response.y > 0)
				entity->SetPlatform(&m_platforms[i]);
			return i;
		}
	}
	
	return -1;
}

bool World::IsUnbounded (Entity * entity) const {
	return !m_bounds.intersects(entity->GetBounds());
}

sf::Vector2f World::GetBaseSpawnPoint (int which) const {
	auto pos = m_platforms.at(which ? m_base1 : m_base0).getGlobalBounds();
	sf::Vector2f spawnpoint = utils::getCenter(pos);
	spawnpoint.y -= pos.height/2.f + 100.f;
	spawnpoint.x += utils::randCentered(50.f);
	return spawnpoint;
}

