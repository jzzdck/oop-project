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
		TrailEffect(m_target, i);
		sf::Color c;
		if (has_deps) {
			m_dep.setOrigin(0,0);
			TrailEffect(m_dep, i);
			win.draw(m_dep);
			c = m_dep.getColor();
			c.a = 255;
		}
		
		win.draw(m_target);
		c = m_target.getColor();
		c.a = 255;
	}
}

void Trail::TrailEffect (sf::Sprite & with_this, int index) {
	with_this.setPosition(m_positions[index]);
	
	// 100% alpha/scale - 10%, 20%, 30%, etc
	float percentage = 1.0f - (1.0f*index/10.0f);
	sf::Color c = with_this.getColor();
	c.a = sf::Uint8(255*percentage);
	with_this.setScale(2*m_scale*percentage, 2*m_scale*percentage);
	with_this.setColor(c);
}

