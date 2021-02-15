#include "MapMenu.h"
#include <iostream>
#include "MapEditor.h"
#include "../Menu_Principal.h"
#include "../../../Game.h"
#include "../../../Utils/textOperations.h"
#include "../../../Utils/generalUtils.h"

MapMenu::MapMenu(float wdt, float hgt) : Menu(wdt, hgt, "maps") {
	m_mapnames = utils::getMapnames();
	
	if (!m_mapnames.empty()) {
		current_map = 0;
		std::string str = m_texts[1].getString();
		std::string aux = "NO MAPS AVAILABLE";
		
		size_t pos = str.find(aux);
		if (pos != std::string::npos)
			str = str.replace(pos, aux.size(), m_mapnames[0]);
		m_texts[1].setString(str);
		utils::center(m_texts[1], {win_width, win_height});
	} else current_map = -1;
}

void MapMenu::Select (Game & g) {
	if (current_map == -1 && current_option == 1)
		current_option = 0;
	
	switch (current_option) {
	case 0:
		g.SetScene(new MapEditor(win_width, win_height));
		break;
	case 1:
		g.SetScene(new MapEditor(win_width, win_height, m_mapnames[current_map]));
		break;
	case 2:
		g.SetScene(new Menu_Principal(win_width, win_height));
		break;
	}
}

void MapMenu::ProcessEvent (sf::Event & e, Game & g) {
	// this menu only cares about key presses
	if (e.type != sf::Event::KeyPressed) return;
	
	if (e.key.code == sf::Keyboard::Escape)
		g.SetScene(new Menu_Principal(win_width, win_height));
	else StandardMenuInput(g, e.key.code);
	
	int dir = e.key.code == m_input.GetKey("go_right") ?  1 : 
			 (e.key.code == m_input.GetKey("go_left")  ? -1 : 0);
	
	// if key pressed isnt left nor right, then return
	if (!dir or current_option == -1) 
		return;
	
	if (current_option == 1) {
		int previous = current_map;
		current_map += dir;
		current_map = utils::wrap(current_map, m_mapnames.size());
		utils::replaceOption(previous, current_map, m_mapnames, m_texts[1]);
		utils::center(m_texts[1], {win_width, win_height});
	}
}

void MapMenu::Update (Game & g) {
	HighlightCurrentOption();
}

void MapMenu::Render (DrawingEnviroment & drawEnv) {
	drawEnv.ClearWindow();
	
	for (auto& text : m_texts)
		drawEnv.AddToLayer(&text,0);
	
	drawEnv.DrawAll();
}
