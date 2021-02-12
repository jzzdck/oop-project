#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "RectangleDrawer.h"

class Grid : public sf::Drawable {
public:
	Grid(const sf::Rect<float> &dims, float resolution);
	void SnapToGrid(RectangleDrawer &rd);
private:
	sf::RectangleShape m_bounds;
	float m_resolution;
	std::vector<std::vector<sf::Vector2f>> grid_points;
	
	sf::Vector2f SnapPos(const sf::Vector2f &pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif

