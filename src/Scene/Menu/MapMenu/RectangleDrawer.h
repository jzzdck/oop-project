#ifndef RECTANGLEDRAWER_H
#define RECTANGLEDRAWER_H
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Line.h"
#include "../../../EntitiesFacade/Platform.h"

class RectangleDrawer : public sf::Drawable {
public:
	enum State {
		Nothing,    Deleting, Painting, 
		Drawing,    Moving,   Circular,
		Horizontal, Vertical
	};
	
	RectangleDrawer(const sf::Rect<float> &bounds, float scale);
	std::string GetRectsInfo(std::string mapname);
	void LoadRects(std::string filename);
	void ProcessEvents(sf::Event &e);
	void Update(sf::RenderWindow &win);
	void SetColor(const sf::Color &to_set);
	State GetState() const;
	std::vector<Platform> &GetRects() { return m_rectangles;}
private:
	void Switcher(State desired);
	float m_scale;
	State m_state;
	sf::Color bucket_color = sf::Color::Red;
	
	std::vector<Platform> m_rectangles;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::Vector2f m_winsize;
	Line m_line;
	bool update = true, simulating = !update;
	std::vector<Platform>::iterator current;
};

#endif

