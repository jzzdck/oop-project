#ifndef PLATAFORM_H
#define PLATAFORM_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../../FileManager.h"

class Plataform {
public:
	Plataform(std::string const& key);
	virtual void Move()=0;
	virtual void Update()=0;
	virtual void LoadData(FileManager const& s_aux,float const& win_width,float const& win_height  )=0;
	void Draw(sf::RenderWindow& w);
	sf::Rect<float> getGlobalBounds()const;
	void setColor(sf::Color const& c);
	sf::Vector2f getSpeed() const { return m_linear_speed + m_angular; }
	
	int isBase()const;
	virtual ~Plataform() = default;
protected:
	sf::Vector2f m_linear_speed = {0, 0}, m_angular = {0, 0};
	
	void setRect(sf::RectangleShape& r);
	void setPos(sf::Vector2f pos);
	const std::string m_key;
	bool m_base;
	bool m_player;
	sf::RectangleShape m_rec;
};

#endif

