#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "../../Utils/FileManager.h"
#include "../../Graphics/DrawingEnviroment.h"

class Platform:public sf::RectangleShape {
public:
	Platform(std::string const& key);
	virtual void Move()=0;
	virtual void Update()=0;
	virtual void LoadData(FileManager const& s_aux,float const& win_width,float const& win_height)=0;
	virtual void Render(DrawingEnviroment& drawEnv);
	
	sf::Vector2f getSpeed() const { return m_linear_speed + m_angular; }
	
	int isBase()const;
	virtual ~Platform() = default;
protected:
	sf::Vector2f m_linear_speed = {0, 0}, m_angular = {0, 0};
	
	const std::string m_key;
	bool m_base;
	bool m_player;
};

#endif

