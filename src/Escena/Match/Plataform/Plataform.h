#ifndef PLATAFORM_H
#define PLATAFORM_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Plataform {
public:
	Plataform();
	virtual void Move(){};
	virtual void Update()=0;
	void Draw();
	sf::Rect<float> getPos();
	sf::Vector2f getSpeed();
	void LoadPlataform();
private:
	sf::Vector2f m_speed;
	sf::RectangleShape m_rec;
};

#endif

