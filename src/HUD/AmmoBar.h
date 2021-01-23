#ifndef AMMOBAR_H
#define AMMOBAR_H
#include "Bar.h"

class AmmoBar : public Bar {
public:
	AmmoBar();
	void Update(const Player *target) override;
private:
	
};

#endif

