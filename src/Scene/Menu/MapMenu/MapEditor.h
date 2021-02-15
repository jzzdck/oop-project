#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include "RectangleDrawer.h"
#include "Grid.h"
#include "InputBox.h"
#include "../Menu.h"

class MapEditor : public Menu {
public:
	MapEditor(float wdt, float hgt, std::string loadmap = "");
	void ProcessEvent (sf::Event & e, Game & g) override;
	void Update (Game & g) override;
	void Render (DrawingEnviroment & drawEnv) override;
protected:
	void Select (Game & g);
private:
	std::map<RectangleDrawer::State, std::string> m_toolnames;
	std::string m_mapname;
	RectangleDrawer m_drawer;
	Grid m_grid;
	InputText m_text;
	bool inputing, has_mapname, first_keystroke = true;
};

#endif

