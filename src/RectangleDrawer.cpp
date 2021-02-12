#include "RectangleDrawer.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>
#include "Utils/FileManager.h"

RectangleDrawer::RectangleDrawer (const sf::Rect<float> &bounds, float scale) :
	m_scale(scale)
{
	m_winsize = { bounds.width, bounds.height };
}

void RectangleDrawer::ProcessEvents (sf::Event & e) {
	sf::Vector2f mousepos = {float(e.mouseButton.x), float(e.mouseButton.y)};
	
	if (e.type == sf::Event::KeyPressed) {
		switch (e.key.code) {
		case sf::Keyboard::A:
			Switcher(Moving);
			break;
		case sf::Keyboard::S:
			m_state = Painting;
			break;
		case sf::Keyboard::D:
			m_state = Deleting;
			break;
		case sf::Keyboard::R:
			Switcher(Circular);
			break;
		case sf::Keyboard::T:
			Switcher(Horizontal);
			break;
		case sf::Keyboard::E:
			Switcher(Vertical);
			break;
		case sf::Keyboard::P:
			simulating = !simulating;
			break;
		}
	} else if (e.mouseButton.button == sf::Mouse::Left && !simulating) {
		if (e.type == sf::Event::MouseButtonPressed) {
			m_state = Drawing;
			m_rectangles.push_back(Platform({0,0}));
			current = m_rectangles.end()-1;
			current->setPosition(mousepos);
			update = false;
		} else if (e.type == sf::Event::MouseButtonReleased) {
			current->ResetStartingPosition();
			m_state = Nothing, update = true;
		}
	}
}

void RectangleDrawer::Update (sf::RenderWindow &win) {
	sf::Vector2i aux = sf::Mouse::getPosition(win);
	sf::Vector2f mousepos = win.mapPixelToCoords(aux);
	
	if (!update || m_state == Nothing)
		current == m_rectangles.end();
	else {
		current = std::find_if(m_rectangles.begin(),m_rectangles.end(),[&](auto &rect) {
			return rect.getGlobalBounds().contains(mousepos);
		});
	}
	
	if (current != m_rectangles.end() && !simulating) {
		sf::Vector2f pos = current->getPosition();
		
		switch (m_state) {
		case Drawing:
			current->setSize(mousepos - pos);
			current->ResetStartingPosition();
			break;
		case Moving:
			current->setPosition(mousepos);
			current->ResetStartingPosition();
			update = false;
			break;
		case Painting:
			current->setFillColor(bucket_color);
			m_state = Nothing;
			break;
		case Deleting:
			m_rectangles.erase(current);
			m_state = Nothing;
			break;
		case Horizontal:
			m_line.SetPoints({mousepos.x, pos.y}, pos);
			current->MakeDynamic({mousepos.x, pos.y}, pos);
			update = false;
			break;
		case Vertical:
			m_line.SetPoints({pos.x, mousepos.y}, pos);
			current->MakeDynamic({pos.x, mousepos.y}, pos);
			update = false;
			break;
		case Circular:
			m_line.SetPoints(mousepos, pos);
			current->MakeCircular(m_line.GetLength(), m_line.GetAngle(), mousepos);
			update = false;
			break;
		}
	}
	
	if (simulating) for (auto &rect : m_rectangles)
		rect.Update();
}

void RectangleDrawer::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	for(size_t i=0;i<m_rectangles.size();i++) 
		target.draw(m_rectangles.at(i));
	
	if (m_state != Circular && m_state != Horizontal && m_state != Vertical) 
		return;
	
	if (!simulating)
		target.draw(m_line);
}

void RectangleDrawer::SetColor (const sf::Color & to_set) {
	bucket_color = to_set;
}

RectangleDrawer::State RectangleDrawer::GetState ( ) const {
	return m_state;
}

std::string RectangleDrawer::GetRectsInfo ( std::string mapname ) {
	std::string info;
	info += "[###]" + mapname + "-static\n";
	info += "scale=" + std::to_string(m_scale) + "\n"; 
	info += "bounds=" + std::to_string(m_winsize.x*m_scale) + " " + std::to_string(m_winsize.y*m_scale) + "\n"; 
	info += "size=" + std::to_string(m_rectangles.size()) + "\n";
	info += "color=100 200 150\n\n";
	
	for (size_t i=0; i<m_rectangles.size(); ++i) 
		info += m_rectangles.at(i).GetStringInfo(m_winsize, m_scale, i);
	
	info += "------------------\n";
	return info;
}

void RectangleDrawer::LoadRects (std::string filename) {
	FileManager s("/maps/" + filename + ".conf", filename + "-static");
	size_t size = std::stoi(s["size"]);
	
	for (int i=0; i<size; ++i) { 
		std::string key = "rect" + std::to_string(i) + "-";
		m_rectangles.push_back(Platform(key, s, m_winsize/m_scale));
	}
	
	current = m_rectangles.end();
}

void RectangleDrawer::Switcher (State desired) {
	if (m_state == desired)
		m_state = Nothing, update = true;
	else
		m_state = desired;
}
