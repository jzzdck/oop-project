#include "Animation.h"
#include <cmath>
#include <iostream>
#include "../Utils/generalUtils.h"

Animation::Animation (sf::Sprite * target, sf::Sprite * indep, std::string sprite_sheet, AnimationInfo info) :
	m_info(info)
{
	std::string path = "../res/spritesheets/";
	m_target = target;
	if (target != nullptr) {
		m_spritesheet.loadFromFile(path + sprite_sheet + "_dep.png");
	}
	
	m_indep = indep;
	if (indep != nullptr)
		m_indeps.loadFromFile(path + sprite_sheet + "_indep.png");
}

void Animation::Update () {
	sf::Rect<int> sub_rect = { int(m_info.dims.x)*m_info.current, 0, int(m_info.dims.x), int(m_info.dims.y)};
	
	if (m_target != nullptr) {
		m_target->setTexture(m_spritesheet, true);
		m_target->setTextureRect(sub_rect);
	}
	
	if (m_indep != nullptr) {
		m_indep->setTexture(m_indeps, true);
		m_indep->setTextureRect(sub_rect);
	}
	
	if (m_clock.getElapsedTime().asSeconds() > m_info.time_step)
		m_clock.restart(), m_info.current++;
	
	if (m_info.current >= m_info.frames && !loopable)
		m_info.current = m_info.frames-1;
	else
		utils::wrap(m_info.current, m_info.frames);
}
