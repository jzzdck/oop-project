#ifndef FLAG_H
#define FLAG_H
#include "Item.h"
#include "../../Graphics/Trail.h"

class Flag : public Item {
public:
	Flag(sf::Vector2f pos, bool who);
	void Render(DrawingEnviroment &drawEnv) override;
	void Update() override;
	void draw(sf::RenderTarget& target,sf::RenderStates states)const override;
	int WasCaptured(int base_index) override;
	void SetOwner(int owner, const sf::Vector2f &release_speed) override;
private:
	int prev_owner = -1;
	int m_who;
	sf::Sprite m_dep;
	Trail m_trail;
};

#endif

