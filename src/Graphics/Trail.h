#ifndef TRAIL_H
#define TRAIL_H
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "DrawingEnviroment.h"
using namespace std;

// graphic class

class Trail : public sf::Drawable {
public:
	Trail(const sf::Sprite &target, bool deps = false, float scale = 1.f);
	void AddPosition(const sf::Vector2f &new_pos);
	void SetDep(const sf::Sprite &dep) { 
			m_dep.resize(1);
			m_dep.at(0) = dep;
	}
	
	void SetIndep(const sf::Sprite &indep) {
			m_target.at(0) = indep;
			m_target.resize(1);
	}
	
	void Render(DrawingEnviroment &drawEnv);
	void Clear() { m_positions.clear(); }
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void TrailEffect(sf::Sprite &with_this, int index);
	
	float m_scale;
	bool has_deps, using_shaders = false;
	std::vector<sf::Sprite> m_target;
	std::vector<sf::Sprite> m_dep;
	std::vector<sf::Vector2f> m_positions;
	sf::Shader m_monochromizer;
};

#endif

