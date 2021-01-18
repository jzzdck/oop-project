#ifndef TRAIL_H
#define TRAIL_H
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
using namespace std;

// graphic class

class Trail {
public:
	Trail(const sf::Sprite &target, bool deps = false, float scale = 1.f);
	void AddPosition(const sf::Vector2f &new_pos);
	void SetDep(const sf::Sprite &dep) { m_dep = dep; }
	void SetIndep(const sf::Sprite &indep) { m_target = indep; }
	void Draw(sf::RenderWindow &win);
	void Clear() { m_positions.clear(); }
private:
	void TrailEffect(sf::Sprite &with_this, int index, sf::RenderWindow &win);
	float m_scale;
	bool has_deps, using_shaders = false;
	sf::Sprite m_target;
	sf::Sprite m_dep;
	std::vector<sf::Vector2f> m_positions;
	sf::Shader m_monochromizer;
};

#endif

