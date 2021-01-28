#include "Animation.h"
#include <cmath>
#include <iostream>

Animation::Animation (sf::Sprite * target, sf::Sprite * indep) {
	time_per_frame = sf::seconds(0.055f);
	
	m_target = target;
	m_indep = indep;
	m_spritesheet.loadFromFile("res/running_dep.png");
	m_indeps.loadFromFile("res/running_indep.png");
}

void Animation::Update () {
	switch (m_state) {
	case State::Running:
		UpdateRun();
		break;
	case State::Jumping:
		break;
	case State::Running | State::Jumping:
		break;
	default:
		current_frame = 0;
		break;
	}
}

void Animation::UpdateRun ( ) {
	sf::Rect<int> sub_rect = { 42*current_frame, 0, 42, 50};
	
	m_target->setTexture(m_spritesheet, true);
	m_target->setTextureRect(sub_rect);
	
	m_indep->setTexture(m_indeps, true);
	m_indep->setTextureRect(sub_rect);
	
	if (m_clock.getElapsedTime().asSeconds() > time_per_frame.asSeconds())
		m_clock.restart(), current_frame++;
	
	if (current_frame >= run_frames)
		current_frame = 0;
}

