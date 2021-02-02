#ifndef TRAIL_H
#define TRAIL_H
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "DrawingEnviroment.h"
using namespace std;

// graphic class

class Trail : public sf::Drawable {
public:
	Trail(const sf::Sprite &target, bool deps = false, float scale = 1.f);
	void AddPosition(const sf::Rect<float> &new_pos, const sf::Vector2f &local_center);
	
	void SetDep(const sf::Sprite &dep);
	void SetIndep(const sf::Sprite &indep);
	void Pop();
	void SetLength(int new_length);
	void SetColor(const sf::Color &c);
	
	void Render(DrawingEnviroment &drawEnv);
	void Clear() { m_positions.clear(); }
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void TrailEffect(sf::Sprite &with_this, int index);
	
	float m_scale;
	int m_length;
	sf::Color m_color;
	bool has_deps;
	
	std::vector<sf::Sprite> m_target;
	std::vector<sf::Sprite> m_dep;
	std::vector<sf::Vector2f> m_positions;
	sf::Shader m_monochromizer;
};

#endif

