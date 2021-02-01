#ifndef BAR_H
#define BAR_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "../Graphics/DrawingEnviroment.h"
#include "../PlayerInfo.h"

class Bar {
public:
	Bar(std::string keyword);
	void SetWidth(float new_width);
	void SetColor(const sf::Color &color);
	
	virtual void Update(const PlayerInfo &info) {};
	void Render(const sf::Vector2f &pos, DrawingEnviroment &drawEnv, float zoom_level, float dir);
protected:
	bool with_background = false;
private:
	sf::RectangleShape m_bar;
	sf::RectangleShape m_background;
	
	sf::Vector2f m_relative_percentage;
	float m_width;
};

#endif

