#include "Trail.h"

Trail::Trail (const sf::Sprite & target, bool deps, float scale) :
	m_target(target), has_deps(deps), m_scale(scale)
{
	m_target.scale(scale,scale);
}

void Trail::AddPosition (const sf::Vector2f & new_pos) {
	m_positions.insert(m_positions.begin(), new_pos);
	if (int(m_positions.size()) > 10)
		m_positions.pop_back();
}

void Trail::Draw (sf::RenderWindow & win) {
	for(size_t i=1; i<m_positions.size(); ++i) { 
		if (has_deps) {
			m_dep.setOrigin(0,0);
			TrailEffect(m_dep, i, win);
		}
		
		TrailEffect(m_target, i, win);
	}
}

void Trail::TrailEffect (sf::Sprite & with_this, int index, sf::RenderWindow &win) {
	with_this.setPosition(m_positions[index]);
	
	// 100% alpha/scale - 10%, 20%, 30%, etc
	float percentage = 1.0f - (1.0f*index/10.0f);
	sf::Color c = with_this.getColor();
	c.a = sf::Uint8(200*percentage);
	with_this.setScale(2*m_scale*percentage, 2*m_scale*percentage);
	with_this.setColor(c);
	win.draw(with_this);
	c.a = 255;
}

