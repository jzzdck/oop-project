#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <sstream>
#include "DynamicPlatformInfo.h"
#include "../Graphics/DrawingEnviroment.h"
#include "../Utils/FileManager.h"

class Platform : public sf::RectangleShape {
public:
	Platform(std::string const& key, FileManager const& s_aux, sf::Vector2f const& winsize);
	Platform(sf::Vector2f const& size);
	void Update ( );
	void Render(DrawingEnviroment& drawEnv);
	int IsBase() const;
	
	void SetAbsolutePosition(const sf::Vector2f &newpos);
	void SetLinearSpeed(sf::Vector2f const& speed);
	void SetAngularSpeed(float speed);
	sf::Vector2f GetSpeed() const;
	void MakeDynamic(const sf::Vector2f &p1, const sf::Vector2f &p2);
	void MakeCircular(float radius, float angle, const sf::Vector2f &p2);
	std::string GetStringInfo(const sf::Vector2f &winsize, float scale, int index) const;
	void ResetStartingPosition();
	
	bool dynamic = false;
private:
	sf::Vector2f total_speed;
	void Rotate();
	void CheckLimits();
	
	sf::Vector2f abpos;
	DynamicInfo m_info;
	int m_player;
};

#endif
