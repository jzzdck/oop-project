#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "Bar.h"

class HealthBar : public Bar {
public:
	HealthBar();
	void Update(const Player* target) override;
private:
};

#endif

