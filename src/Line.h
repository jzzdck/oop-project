#ifndef LINE_H
#define LINE_H
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Line : public sf::VertexArray {
public:
	Line() = default;
	void SetPoints(const sf::Vector2f &p1, const sf::Vector2f &p2);
	float GetLength() const;
	float GetAngle() const;
private:
	sf::Vector2f GetPoint(int which) const { return arr[which].position; }
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::VertexArray arr;
};

#endif

