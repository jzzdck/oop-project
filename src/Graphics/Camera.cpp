#include "Camera.h"
#include <cmath>
#include "../Utils/generalUtils.h"

Camera::Camera(float width, float height) :
	m_width(width), m_height(height),m_increment(0)
{
	m_view.setCenter(m_width*utils::randf(), m_height*utils::randf());
	m_view.setSize(0,0);
}


void Camera::Update ( const CameraInfo &info ) {
	auto prev_center = m_view.getCenter();
	
	if (info.living_states[0] && info.living_states[1]) {
		auto sp0 = info.global_bounds[0];
		auto sp1 = info.global_bounds[1]; 
		
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
	} else for (size_t i=0;i<info.living_states.size();i++) { 
		if (info.living_states[i]) {
			auto sp0 = info.global_bounds[i];
			target_center = utils::getCenter(sp0);
			cam_size = {sp0.width, sp0.height};
		}
	}
	
	m_view.setCenter({ 
		prev_center.x*0.90f + target_center.x*0.1f,
		prev_center.y*0.90f + target_center.y*0.1f
	});
	
	m_view.setSize( {m_width, m_height} );
	float new_zoom = std::max(cam_size.x/m_width + 0.36f +m_increment*m_zoom, cam_size.y/m_height + 0.36f+m_increment*m_zoom);
	m_zoom = new_zoom*0.05 + m_zoom*0.95;
	m_view.zoom(m_zoom);
}

void Camera::SetToWindow (sf::RenderWindow & win) {
	win.setView(m_view);
}

void Camera::In_De_creaseZoom(float porcentual_increment) {
	m_increment += porcentual_increment;
}
