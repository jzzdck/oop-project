#include "Trail.h"
#include <iostream>
#include "../Utils/generalUtils.h"

Trail::Trail (const sf::Sprite & target, bool deps, float scale) :
	has_deps(deps), m_scale(scale), m_length(15), m_color(sf::Color::White)
{
	m_target.resize(1);
	m_target.at(0) = target;
	m_target.at(0).scale(scale,scale);
	
	if (!sf::Shader::isAvailable())
		std::cerr << "Shaders aren't available" << std::endl;
	else if (!m_monochromizer.loadFromFile("Graphics/Shaders/solid_color.frag", sf::Shader::Fragment))
		std::cerr << "Couldn't load shaders" << std::endl;
}

void Trail::AddPosition (const sf::Rect<float> & bounds, const sf::Vector2f &local_center) {
	sf::Vector2f new_pos = utils::getCenter(bounds);
	
	m_positions.insert(m_positions.begin(), new_pos);
	m_target.insert(m_target.begin(), m_target.at(0));
	m_target.at(0).setOrigin(local_center);
	
	if (has_deps) {
		m_dep.insert(m_dep.begin(), m_dep.at(0));
		m_dep.at(0).setOrigin(local_center);
	}

	if (int(m_positions.size()) > m_length) {
		m_positions.pop_back();
		if (has_deps) m_dep.pop_back();
		m_target.pop_back();
	}
}

void Trail::Render (DrawingEnviroment &drawEnv) {
	for (size_t i=1; i<m_positions.size(); ++i) {
		if (has_deps)
			TrailEffect(m_dep[i], i);
		
		TrailEffect(m_target[i], i);
	}
	
	drawEnv.AddToLayer(this, 8);
}

void Trail::TrailEffect (sf::Sprite & with_this, int index) {
	// 100% alpha/scale - 10%, 20%, 30%, etc
	float percentage = 1.0f - (1.0f*index/float(m_length));
	with_this.setScale(2*m_scale*percentage, 2*m_scale*percentage);
	
	with_this.setPosition(m_positions[index]);
	m_monochromizer.setUniform("texture", sf::Shader::CurrentTexture);
	m_monochromizer.setUniform("color", sf::Glsl::Vec4(m_color));
}

void Trail::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	for(size_t i=1;i<m_positions.size();i++) {
		if (has_deps)
			target.draw(m_dep[i], &m_monochromizer);
		
		target.draw(m_target[i], &m_monochromizer);
	}
}

void Trail::SetDep (const sf::Sprite & dep) {
	m_dep.resize(1);
	m_dep.at(0) = dep;
}

void Trail::SetIndep (const sf::Sprite & indep) {
	m_target.at(0) = indep;
	m_target.resize(1);
}

void Trail::Pop ( ) {
	if (m_positions.size() > 0) {
		m_positions.pop_back();
		m_target.pop_back();
		if (has_deps)
			m_dep.pop_back();
	}
}

void Trail::SetLength (int new_length) {
	m_length = new_length;
}

void Trail::SetColor (const sf::Color & c) {
	m_color = c;
}

