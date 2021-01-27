#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <vector>
#include "Plataform/Plataform.h"
#include "../../Entity/Entity.h"
#include "../../Graphics/DrawingEnviroment.h"

/** @brief The World class is the place where the Match occurs **/
class World {
public:
	void Update();
	void Render(DrawingEnviroment& drawEnv);
	
	float GetGravity() const { return m_gravity; }
	int CollidesWith(Entity *entity, sf::Vector2f &response, int index = 0);
	int GetBaseIndex(int which) const { return which ? m_base1 : m_base0; };
	
	World(float wdt, float hgt, float gravity, std::string map_name = "MAIN");
	~World();
private:
	void LoadMap(std::string map_name);
	std::vector<Plataform*> m_platforms;
	float m_gravity;
	float win_width, win_height;
	std::string m_map;
	int m_base0, m_base1;
	sf::Color m_c;
};

#endif

