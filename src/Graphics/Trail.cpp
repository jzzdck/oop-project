#include "Trail.h"
#include <iostream>

Trail::Trail (const sf::Sprite & target, bool deps, float scale) :
	m_target(target), has_deps(deps), m_scale(scale)
{
	m_target.scale(scale,scale);
	
	if (!sf::Shader::isAvailable())
		std::cerr << "Shaders aren't available" << std::endl;
	else if (!m_monochromizer.loadFromFile("src/Graphics/Shaders/solid_color.frag", sf::Shader::Fragment))
		std::cerr << "Couldn't load shaders" << std::endl;
	else
		using_shaders = true;
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
	// 100% alpha/scale - 10%, 20%, 30%, etc
	float percentage = 1.0f - (1.0f*index/10.0f);
	sf::Color shader_color = has_deps ? m_dep.getColor() : sf::Color::Red;
	shader_color.a = 200*percentage;
	with_this.setScale(2*m_scale*percentage, 2*m_scale*percentage);
	
	with_this.setPosition(m_positions[index]);
	m_monochromizer.setUniform("texture", sf::Shader::CurrentTexture);
	m_monochromizer.setUniform("color", sf::Glsl::Vec4(shader_color));
	win.draw(with_this, &m_monochromizer);
}

