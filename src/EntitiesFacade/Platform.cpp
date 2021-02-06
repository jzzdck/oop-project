#include "Platform.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "../Utils/generalUtils.h"

Platform::Platform(std::string const& key, const FileManager & s_aux, const sf::Vector2f &winsize)
{
	sf::Rect<float> dim = utils::getRectDim(s_aux[key+"dim"]);
	setSize({dim.width * winsize.x, dim.height * winsize.y});
	setPosition({dim.left * winsize.x, dim.top * winsize.y});
	
	m_player = std::stoi(s_aux[key + "base-info"]);
	if (m_player != -1)
		setFillColor(utils::loadPlayerColor(m_player));
	else
		setFillColor(utils::getColor(s_aux["color"]));
	
	abpos = utils::getXY(s_aux[key + "abs-pos"]);
	abpos.x *= winsize.x; abpos.y *= winsize.y;
	if (s_aux[key + "is-dynamic"] == "YES") {
		m_info = s_aux[key + "dynamic-info"];
		m_info.start_pos.x *= winsize.x, m_info.start_pos.y *= winsize.y;
		m_info.end_pos.x *= winsize.x, m_info.end_pos.y *= winsize.y;
		m_info.radius *= winsize.y;
		dynamic = true;
	}
}

Platform::Platform (const sf::Vector2f & size) {
	setSize(size);
	m_player = -1;
}

void Platform::Update ( ) {
	total_speed = getPosition();
	Rotate();
	
	abpos += m_info.linear_speed;
	setPosition(abpos + m_info.ang_speed);
	CheckLimits();
	
	total_speed = getPosition() - total_speed;
}

void Platform::Render(DrawingEnviroment& drawEnv) {
	int layer = 4;
	auto aux = m_info.linear_speed + m_info.ang_speed;
	if (aux.x or aux.y)
		layer++;
	
	drawEnv.AddToLayer(this, layer);
}

int Platform::IsBase() const {
	return m_player;
}

void Platform::SetLinearSpeed (const sf::Vector2f & speed) {
	m_info.linear_speed = speed;
}

void Platform::SetAngularSpeed (float speed) {
	m_info.angle_vel = speed;
}

void Platform::Rotate ( ) {
	m_info.angle += m_info.angle_vel;
	m_info.ang_speed = {
		m_info.radius*std::cos(m_info.angle*3.14f/180.f), 
		m_info.radius*std::sin(m_info.angle*3.14f/180.f)
	};
}

void Platform::CheckLimits ( ) {
	auto end_pos = m_info.end_pos + m_info.start_pos;

	if (abpos.x<m_info.start_pos.x or abpos.x>end_pos.x)
		m_info.linear_speed.x *= -1.f;
	
	if (abpos.y<m_info.start_pos.y or abpos.y>end_pos.y)
		m_info.linear_speed.y *= -1.f;
}

sf::Vector2f Platform::GetSpeed ( ) const {
	return total_speed;
}

std::string Platform::GetStringInfo (const sf::Vector2f & winsize, float scale, int index) const {
	std::string info;
	auto bounds = getGlobalBounds(); auto auxpos = abpos;
	auxpos.x *= scale/winsize.x; auxpos.y *= scale/winsize.y;
	bounds.left *= scale/winsize.x; bounds.top *= scale/winsize.y;
	bounds.width *= scale/winsize.x; bounds.height *= scale/winsize.y;
	
	std::string key = "rect" + std::to_string(index);		
	std::string aux = std::to_string(auxpos.x) + " " + std::to_string(auxpos.y);
	info += key + "-dim=" + utils::rectDimsToString(bounds) + "\n";
	info += key + "-abs-pos=" + aux + "\n";
	info += key + "-base-info=" + std::to_string(m_player) + "\n";
	
	if (dynamic) {
		info += key + "-is-dynamic=YES\n";
		info += key + "-dynamic-info=" + m_info.GetString(winsize, scale) + "\n";
	} else
		info += key + "-is-dynamic=NO\n";
	
	info += "\n";
	return info;
}

void Platform::ResetStartingPosition () {
	m_info.start_pos = getPosition();
	abpos = getPosition();
}

void Platform::MakeDynamic (const sf::Vector2f &p1, const sf::Vector2f &p2) {
	dynamic = true;
	m_info.Reset();
	abpos = p2;
	
	if (std::hypot(p1.x,p1.y) < std::hypot(p2.x,p2.y))
		m_info.start_pos = p1, m_info.end_pos = p2-p1;
	else
		m_info.start_pos = p2, m_info.end_pos = p1-p2;
	
	if (p1.y == p2.y)
		m_info.linear_speed = {1, 0};
	else
		m_info.linear_speed = {0, 1};
}

void Platform::MakeCircular (float radius, float angle, const sf::Vector2f &mousepos) {
	dynamic = true;
	m_info.Reset();
	abpos = mousepos;
	m_info.angle = angle;
	m_info.radius = radius;
	m_info.angle_vel = 1.f;
}

void Platform::SetAbsolutePosition (const sf::Vector2f & newpos) {
	abpos = newpos;
}

