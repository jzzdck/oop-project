#include "Line.h"
#include <cmath>

void Line::SetPoints (const sf::Vector2f & p1, const sf::Vector2f & p2) {
	arr.setPrimitiveType(sf::Lines);
	arr.clear();
	arr.append({p1, sf::Color::Red});
	arr.append({p2, sf::Color::Red});
}

void Line::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(arr);
}

float Line::GetLength ( ) const {
	sf::Vector2f p1 = GetPoint(0), p2 = GetPoint(1);
	
	return std::hypot(p2.x-p1.x, p2.y-p1.y);
}

float Line::GetAngle ( ) const {
	sf::Vector2f p1 = GetPoint(0), p2 = GetPoint(1);
	
	return std::atan2(p2.y-p1.y, p2.x-p1.x) * 180.f / M_PI;
}

