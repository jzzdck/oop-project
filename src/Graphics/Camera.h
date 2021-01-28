#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include "../Entity/Player.h"

class Camera {
public:
	Camera(float width, float height);
	void Update();
	float GetZoom() { return m_zoom; }
	void SetPlayers(std::vector<Player*> m_players);
	void SetToWindow(sf::RenderWindow &win);
private:
	std::vector<Player*> m_players;
	sf::View m_view;
	sf::Vector2f target_center, cam_size;
	float m_width, m_height, m_zoom = 1.f;
};

#endif
