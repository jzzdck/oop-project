#include "Animation.h"
#include <cmath>
#include <iostream>
#include "../Utils/generalUtils.h"

Animation::Animation (sf::Sprite * target, sf::Sprite * indep, std::string sprite_sheet, AnimationInfo info) :
	m_info(info)
{
	if (target != nullptr) {
		m_target = target;
		m_spritesheet.loadFromFile("../res/spritesheets/" + sprite_sheet + "_dep.png");
	}
	
	if (indep != nullptr) {
		m_indep = indep;
		m_indeps.loadFromFile("../res/spritesheets/" + sprite_sheet + "_indep.png");
	}
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
