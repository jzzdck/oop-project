#include "Trail.h"
#include <iostream>

Trail::Trail (const sf::Sprite & target, bool deps, float scale) :
	has_deps(deps), m_scale(scale)
{
	m_target.resize(1);
	m_target.at(0) = target;
	m_target.at(0).scale(scale,scale);
	
	if (!sf::Shader::isAvailable())
		std::cerr << "Shaders aren't available" << std::endl;
	else if (!m_monochromizer.loadFromFile("src/Graphics/Shaders/solid_color.frag", sf::Shader::Fragment))
		std::cerr << "Couldn't load shaders" << std::endl;
	else
		using_shaders = true;
}

void Trail::AddPosition (const sf::Vector2f & new_pos) {
	m_positions.insert(m_positions.begin(), new_pos);
	m_target.insert(m_target.begin(), m_target.at(0));
	if (has_deps) 
		m_dep.insert(m_dep.begin(), m_dep.at(0));

	if (int(m_positions.size()) > 10) {
		m_positions.pop_back();
		if (has_deps) 
			m_dep.pop_back();
		m_target.pop_back();
	}
}

void Trail::Render (DrawingEnviroment &drawEnv) {
	std::cout << m_positions.size() << endl;
	for(size_t i=1; i<m_positions.size(); ++i) {
		cout << m_positions[i].x << std::endl;
		if (has_deps) {
			m_dep.at(i).setOrigin(0,0);
			TrailEffect(m_dep[i], i);
		}
		
		TrailEffect(m_target[i], i);
	}
	
	drawEnv.AddToLayer(this, 3);
}

void Trail::TrailEffect (sf::Sprite & with_this, int index) {
	// 100% alpha/scale - 10%, 20%, 30%, etc
	float percentage = 1.0f - (1.0f*index/10.0f);
	sf::Color shader_color = has_deps ? m_dep.at(index).getColor() : sf::Color::Red;
	with_this.setScale(2*m_scale*percentage, 2*m_scale*percentage);
	
	with_this.setPosition(m_positions[index]);
	m_monochromizer.setUniform("texture", sf::Shader::CurrentTexture);
	m_monochromizer.setUniform("color", sf::Glsl::Vec4(shader_color));
}

void Trail::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	for(size_t i=1;i<m_positions.size();i++) {
		if (has_deps)
			target.draw(m_dep[i], &m_monochromizer);
		
		target.draw(m_target[i], &m_monochromizer);
	}
}

