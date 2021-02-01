#ifndef PLATFORM_DYNAMIC_H
#define PLATFORM_DYNAMIC_H
#include "Platform.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Platform_dynamic : public Platform {
public:
	Platform_dynamic(std::string key);
	void Move ();
	void Update ( );
	void LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  );
	void Render(DrawingEnviroment& drawEnv)override;
	float getAngSpeed()const;
	
	void setLSpeed(sf::Vector2f const& speed);
	void setAngSpeed(float const& speed);
	
	bool CheckLimits(bool const& axis);
	void InvertLSpeed(bool const& axis);
	void InvertAngSpeed();
	
	void Rotate();
private:
	sf::Vector2f m_start, m_end;
	float m_angular_speed,m_radius,m_angle;
	
};

#endif

