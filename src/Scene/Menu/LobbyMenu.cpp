#include "LobbyMenu.h"
#include <fstream>
#include "Menu_Principal.h"
#include "../../Utils/generalUtils.h"
#include "../Match/Match.h"
#include "../../TextOperations.h"

LobbyMenu::LobbyMenu(float width, float height) : 
	Menu(width, height, "lobby"), winsize(sf::Vector2f(width, height)) 
{
	m_roundtypes = { 
		"RANDOM", "POINTS", "TIMED", "BOTH" 
	};
	
	m_descriptions = { 
		"Every round is different \nand decided at random.", // random
		
		"The first player to score << 7 >>\npoints wins the round.", // points
		
		"The player who scored more points\nwhen the clock stops wins the round.\n" 
		"Clock will stop at: << 60 >> seconds.", // timed
		
		"A combination of the previous types,\n" // both
		"The player who scores 7 points OR\n"
		"scored more points when the clock\n"
		"stops, wins the round.\n" // both
		"Clock will stop at: 60 seconds" // both
	};
	
	utils::replaceOption(0, m_settings.round_type, m_roundtypes, m_texts[1]);
	utils::center(m_texts[1], winsize);
	m_texts[2].setString(m_descriptions[m_settings.round_type]);
	current_option = 3;
	m_texts[current_option].setStyle(sf::Text::Bold);
	m_texts[2].setStyle(sf::Text::Italic);
}

void LobbyMenu::Select (Game & g) {
	switch (current_option) {
	case 3:
		if (m_settings.round_type != 0)
			m_settings.random_rounds = false;
		else
			m_settings.Randomize();
		
		m_settings.map_name = utils::getRandomMap();
		g.SetScene(new Match(m_settings, winsize.x, winsize.y));
		break;
	case 4:
		g.SetScene(new Menu_Principal(winsize.x, winsize.y));
		break;
	}
}

void LobbyMenu::ProcessEvent (sf::Event & e, Game & g) {
	// this menu only cares about key presses
	if (e.type != sf::Event::KeyPressed) return;
	
	if (e.key.code == sf::Keyboard::Escape)
		g.SetScene(new Menu_Principal(win_width, win_height));
	else StandardMenuInput(g, e.key.code);
	
	int dir = e.key.code == m_input.GetKey("go_right") ?  1 : 
			 (e.key.code == m_input.GetKey("go_left")  ? -1 : 0);
	
	// if key pressed isnt left nor right, then return
	if (!dir) return;
	switch (current_option) {
	case 0:
		m_settings.rounds_left += dir;
		m_settings.rounds_left = std::max(m_settings.rounds_left, 1);
		break;
	case 1: {
		int current = m_settings.round_type;
		m_settings.round_type += dir;
		m_settings.round_type = utils::wrap(m_settings.round_type, m_roundtypes.size());
		utils::replaceOption(current, m_settings.round_type, m_roundtypes, m_texts[1]);
		utils::center(m_texts[1], winsize);
		m_texts[2].setString(m_descriptions[m_settings.round_type]);
		break;
	} case 2:
		if (m_settings.round_type != 1) return;
		m_settings.max_points += dir;
		m_settings.max_points = std::max(m_settings.max_points, 1);
		break;
	}
}

void LobbyMenu::Update (Game & g) {	
	HighlightCurrentOption();
	
	if (current_option == 2 && m_settings.round_type == 2) {
		if (m_input.KeyState("go_left") && m_settings.max_seconds > 5)
			m_settings.max_seconds--;
		else if (m_input.KeyState("go_right"))
			m_settings.max_seconds++;
	}
	
	utils::replaceNumber(m_settings.rounds_left, m_texts[0]);
	utils::center(m_texts[0], winsize);
	if (m_settings.round_type == 1 || m_settings.round_type == 3)
		utils::replaceNumber(m_settings.max_points, m_texts[2]);
	
	if (m_settings.round_type == 2 || m_settings.round_type == 3) {
		size_t pos = m_texts[2].getString().find("Clock");
		utils::replaceNumber(m_settings.max_seconds, m_texts[2], pos);
	}
	
	utils::center(m_texts[2], winsize);
}

void LobbyMenu::Render (DrawingEnviroment & drawEnv) {
	drawEnv.ClearWindow();
	
	for (auto& text : m_texts)
		drawEnv.AddToLayer(&text,0);
	
	drawEnv.DrawAll();
}
