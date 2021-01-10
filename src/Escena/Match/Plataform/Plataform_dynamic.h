#ifndef PLATAFORM_DYNAMIC_H
#define PLATAFORM_DYNAMIC_H
#include "Plataform.h"

class Plataform_dynamic : public Plataform {
public:
	Plataform_dynamic(std::string key);
	void Move ();
	void Update ( );
	void LoadData (FileManager const& s_aux,float const& win_width,float const& win_height  );
	
	sf::Vector2f getLSpeed()const;
	float getAngSpeed()const;
	
	void setLSpeed(sf::Vector2f const& speed);
	void setAngSpeed(float const& speed);
	
	bool CheckLimits(bool const& axis);
	void InvertLSpeed(bool const& axis);
private:
	sf::Vector2f m_linear_speed,m_start,m_end;
	float m_angular_speed;
	
	
};

#endif

