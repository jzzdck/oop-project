#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "Bar.h"
#include "../Entity/EntitiesFacade.h"

class HealthBar : public Bar {
public:
	HealthBar();
	void Update(const PlayerInfo &info) override;
private:
};

#endif

