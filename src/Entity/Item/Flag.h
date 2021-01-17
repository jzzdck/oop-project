#ifndef FLAG_H
#define FLAG_H
#include "Item.h"
#include "../../Graphics/Trail.h"

class Flag : public Item {
public:
	Flag(sf::Vector2f pos, bool who);
	void Draw(sf::RenderWindow & win) override;
	void Update() override;
private:
	sf::Sprite m_dep;
	Trail m_trail;
};

#endif

