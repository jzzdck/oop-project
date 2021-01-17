#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include "../Entity/Player.h"
using namespace std;

class Camera {
public:
	Camera(float width, float height);
	void Update();
	void SetPlayers(vector<Player*> m_players);
	void SetToWindow(sf::RenderWindow &win);
private:
	vector<Player*> m_players;
	sf::View m_view;
	sf::Vector2f target_center, cam_size;
	float m_width, m_height, m_zoom = 1.f;
};

#endif

