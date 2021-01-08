#ifndef PLATAFORM_H
#define PLATAFORM_H
#include <SFML/Graphics/RectangleShape.hpp>

class Plataform {
public:
	Plataform();
	virtual void Move(){};
	virtual void Update()=0;
	void Draw();
	void LoadPlataform();
private:
	sf::Vector2f speed
	sf::Rect pos;
	sf::RectangleShape m_rec;
};

#endif

