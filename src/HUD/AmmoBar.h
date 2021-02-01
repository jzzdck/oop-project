#ifndef AMMOBAR_H
#define AMMOBAR_H
#include "Bar.h"

class AmmoBar : public Bar {
public:
	AmmoBar();
	void Update(const PlayerInfo &info) override;
private:
	
};

#endif

