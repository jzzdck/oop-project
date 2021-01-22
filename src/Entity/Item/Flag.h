#ifndef FLAG_H
#define FLAG_H
#include "Item.h"
#include "../../Graphics/Trail.h"

class Flag : public Item {
public:
	Flag(sf::Vector2f pos, bool who);
	void Draw(sf::RenderWindow & win) override;
	void Update() override;
	
	bool IsTheFlag() const override { return true; }
	void SetOwner(int owner) override;
	int PreviousOwner() const override { return prev_owner; }
	int BelongsTo() const override { return m_who; }
private:
	int prev_owner = -1;
	int m_who;
	sf::Sprite m_dep;
	Trail m_trail;
};

#endif

