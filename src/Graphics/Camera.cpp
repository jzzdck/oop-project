#include "Camera.h"
#include <cmath>

Camera::Camera(float width, float height) :
	m_width(width), m_height(height)
{
	m_view.setCenter(m_width*utils::randf(), m_height*utils::randf());
	m_view.setSize(0,0);
}

void Camera::Update ( ) {
	sf::Vector2f prev_center = m_view.getCenter();
	
	if (m_players[0]->IsAlive() && m_players[1]->IsAlive()) {
		auto sp0 = m_players[0]->GetSprite().getGlobalBounds();
		auto sp1 = m_players[1]->GetSprite().getGlobalBounds(); 
		
		sf::Vector2f center0 = utils::getCenter(sp0);
		sf::Vector2f center1 = utils::getCenter(sp1);
		
		cam_size = { 
			std::fabs(center1.x - center0.x),
			std::fabs(center1.y - center0.y) 
		};
		
		target_center = { 
			cam_size.x/2.f + std::min(center0.x, center1.x), 
			cam_size.y/2.f + std::min(center0.y, center1.y)
		};
	} else {
		for (size_t i=0;i<m_players.size();i++) { 
			if (m_players[i]->IsAlive()) {
				auto sp0 = m_players[i]->GetSprite().getGlobalBounds();
				target_center = utils::getCenter(sp0);
				prev_center = m_view.getCenter();
				cam_size = {sp0.width, sp0.height};
			}
		}
	}
	
	m_view.setCenter({ 
		prev_center.x*0.97f + target_center.x*0.03f,
		prev_center.y*0.97f + target_center.y*0.03f
	});
	
	m_view.setSize( {m_width, m_height} );
	float new_zoom = std::max(cam_size.x/m_width + 0.36f, cam_size.y/m_height + 0.36f);
	m_zoom = new_zoom*0.05 + m_zoom*0.95;
	m_view.zoom(m_zoom);
}

void Camera::SetToWindow (sf::RenderWindow & win) {
	win.setView(m_view);
}

void Camera::SetPlayers (std::vector<Player*> players) {
	m_players = players;
}

