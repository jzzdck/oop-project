#include "Grid.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

Grid::Grid (const sf::Rect<float> & dims, float resolution) :
	m_resolution(resolution)
{	
	m_bounds.setSize({dims.width-11.f, dims.height-7.f});
	m_bounds.setPosition({ dims.left-1.f, dims.top-1.f });
	m_bounds.setFillColor(sf::Color::Transparent);
	m_bounds.setOutlineThickness(10000);
	m_bounds.setOutlineColor(sf::Color::Black);
	
	float cols = dims.width/resolution, rows = dims.height/resolution;
	grid_points.resize(round(cols));
	
	for(size_t i=0;i<grid_points.size();i++) { 
		grid_points.at(i).resize(round(rows));
		for(size_t j=0;j<grid_points.at(0).size();j++) { 
			float x = dims.left + i * resolution;
			float y = dims.top  + j * resolution;
			grid_points[i][j] = { x, y };
		} 
	}
}

void Grid::SnapToGrid (RectangleDrawer &rd) {
	auto &rects = rd.GetRects();
	for (auto &to_snap : rects) {
		if (to_snap.dynamic) continue;
		
		sf::Vector2f pos = to_snap.getPosition();
		to_snap.setPosition(SnapPos(pos));
		to_snap.ResetStartingPosition();
		
		if (rd.GetState() != RectangleDrawer::State::Moving) {
			sf::Vector2f aux = SnapPos(pos + to_snap.getSize());
			sf::Vector2f size = aux - pos;
			size = { 
				std::max(size.x, m_resolution),
				std::max(size.y, m_resolution)
			};
			
			to_snap.setSize(size);
		}
	}
}

void Grid::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	sf::Color c = sf::Color::White;
	c.a = 80;
	
	for(size_t i=0;i<grid_points.at(0).size();i++) { 
		sf::Vertex line[] = {
			sf::Vertex(grid_points[0][i], c),
			sf::Vertex(grid_points[grid_points.size()-1][i], c)
		};
		
		target.draw(line, 2, sf::Lines);
	}
	
	for(size_t i=0;i<grid_points.size();i++) { 
		sf::Vertex line[] = {
			sf::Vertex(grid_points[i][0], c),
			sf::Vertex(grid_points[i][grid_points[0].size()-1], c)
		};
		
		target.draw(line, 2, sf::Lines);
	}
	
	target.draw(m_bounds);
}

sf::Vector2f Grid::SnapPos (const sf::Vector2f & pos) {
	auto y_snap = std::min_element(grid_points.at(0).begin(), grid_points.at(0).end(), 
		[&](sf::Vector2f &v1, sf::Vector2f &v2) {
		   return std::fabs(v1.y - pos.y) < std::fabs(v2.y - pos.y);
		}
	);
	
	int yndex = y_snap - grid_points.at(0).begin();
	auto x_snap = std::min_element(grid_points.begin(), grid_points.end(), 
		[&](std::vector<sf::Vector2f> &v1, std::vector<sf::Vector2f> &v2) {
			return std::fabs(v1.at(yndex).x - pos.x) < std::fabs(v2.at(yndex).x - pos.x);
		}
	);
	
	return { x_snap->at(yndex).x, y_snap->y };
}
