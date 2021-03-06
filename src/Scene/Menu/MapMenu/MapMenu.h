#ifndef MAPMENU_H
#define MAPMENU_H
#include <string>
#include <vector>
#include "../Menu.h"

class MapMenu : public Menu {
public:
	MapMenu(float wdt, float hgt);
	void ProcessEvent (sf::Event & e, Game & g) override;
	void Update (Game & g) override;
	void Render (DrawingEnviroment & drawEnv) override;
protected:
	void Select (Game & g);
private:
	std::vector<std::string> m_mapnames;
	int current_map;
};

#endif

