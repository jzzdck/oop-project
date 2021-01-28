#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include "../Entity/Player.h"
#include "../Entity/EntitiesFacade.h"

class Camera {
public:
	Camera(float width, float height);
	void Update(const CameraInfo &info);
	float GetZoom() { return m_zoom; }
	void SetPlayers(CameraInfo inf);
	void SetToWindow(sf::RenderWindow &win);
private:
	sf::View m_view;
	sf::Vector2f target_center, cam_size;
	float m_width, m_height, m_zoom = 1.f;
};

#endif
