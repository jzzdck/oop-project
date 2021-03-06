#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <vector>
#include "Platform.h"
#include "../Entity/Entity.h"
#include "../Graphics/DrawingEnviroment.h"

/** @brief The World class is the place where the Match occurs **/
class World {
public:
	void Update();
	void Render(DrawingEnviroment& drawEnv);
	
	sf::Rect<float> GetWorldBounds() { return m_bounds; }
	sf::Vector2f GetGravity() const { return {0.f, m_gravity}; }
	int CollidesWith(Entity *entity, sf::Vector2f &response, int index = 0);
	int GetBaseIndex(int which) const { return which ? m_base1 : m_base0; };
	sf::Vector2f GetBaseSpawnPoint(int which) const;
 	bool IsUnbounded(Entity* entity) const;
	
	World(float wdt, float hgt, float gravity, std::string map_name = "MAIN");
	~World();
private:
	sf::Rect<float> m_bounds;
	
	void LoadMap(std::string map_name);
	std::vector<Platform> m_platforms;
	float m_gravity;
	float win_width, win_height;
	std::string m_map;
	int m_base0, m_base1;
	sf::Color m_c;
};

#endif

