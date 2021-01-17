#include "World.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../Utils/FileManager.h"
#include "../../Utils/generalUtils.h"
#include "Plataform/Plataform_static.h"
#include <vector>
#include "Plataform/Plataform_dynamic.h"
#include "../../Utils/CollisionUtil.h"

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
	size_t size2=stoi(s2["size"]);
	
	for(size_t i=0;i<size1;++i)	{
		m_platforms.push_back(new Plataform_static("rect" + std::to_string(i) + "-"));
		m_platforms[i]->LoadData(s1,win_width,win_height);
		if (m_platforms[i]->isBase()!=-1) {
			if (m_platforms[i]->isBase()==0)
				m_base0=i;
			else
				m_base1=i;
		}
	}
	
	for(size_t i=0;i<size2;i++) {
		m_platforms.push_back(new Plataform_dynamic("rect" + std::to_string(i) + "-"));
		m_platforms[i+size1]->LoadData(s2,win_width,win_height);
	}
}

void World::Update() {
	for(Plataform* &x :m_platforms)
		x->Update();
}

void World::Draw (sf::RenderWindow& win) {
	for (Plataform* &p: m_platforms)
		p->Draw(win);
}

World::~World() {
	for(size_t i=0;i<m_platforms.size();i++) 
		delete m_platforms[i];
}

int World::CollidesWith (Entity * entity, sf::Vector2f & response, int index) {
	if (index >= m_platforms.size()) return -1;
	
	utils::Box entity_box = {
		entity->GetSprite().getGlobalBounds(), 
			entity->GetSpeed()
	};
	
	for (size_t i = index; i < m_platforms.size(); ++i) {
		utils::Box platform_box = {
			m_platforms[i]->getGlobalBounds(), 
				m_platforms[i]->getSpeed()
		};
		
		sf::Rect<float> md = utils::minkowskiDifference(entity_box, platform_box);
		if (utils::minkowskiCollision(md)) {
			entity->SetPlatform(m_platforms[i]);
			response = utils::getPenetration(md);
			return i;
		}
	}
	
	return -1;
}

