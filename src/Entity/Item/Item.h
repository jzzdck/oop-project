#ifndef ITEM_H
#define ITEM_H
#include "../Entity.h"
#include "../../Graphics/DrawingEnviroment.h"

class Item : public Entity {
public:
	Item(sf::Vector2f pos, std::string keyword);
	void ApplyResponse(const sf::Vector2f &vec) override;
	void SetUsing(bool use) { in_use = use; }
	
	int Owner() const { return m_owner; }
	virtual void SetOwner(int owner) { m_owner = owner; }
	virtual int PreviousOwner() const { return -2; }
	virtual bool IsTheFlag() const { return false; }
	virtual int BelongsTo() const { return -1; }
	
	void Update() override;
	virtual void Render(DrawingEnviroment &drawEnv);
	virtual ~Item() { }
private:
	void Render() override {};
	int m_owner;
};

#endif

