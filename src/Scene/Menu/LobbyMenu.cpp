#include "LobbyMenu.h"
#include <fstream>
#include "Menu_Principal.h"
#include "../../Utils/generalUtils.h"
#include "../Match/Match.h"

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
	
	ReplaceRoundType(m_settings.round_type, 0);
	current_option = 3;
	m_texts[current_option].setStyle(sf::Text::Bold);
	m_texts[2].setStyle(sf::Text::Italic);
}

void LobbyMenu::Select (Game & g) {
	switch (current_option) 
	{
	case 3:
		if (m_settings.round_type != 0)
			m_settings.random_rounds = false;
		else
			m_settings.Randomize();
		
		m_settings.map_name = GetRandomMap();
		g.SetScene(new Match(m_settings, winsize.x, winsize.y));
		break;
	case 4:
		g.SetScene(new Menu_Principal(winsize.x, winsize.y));
		break;
	}
}

void LobbyMenu::ProcessEvent (sf::Event & e, Game & g) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Escape)
			g.SetScene(new Menu_Principal(win_width, win_height));
		else if (e.key.code == m_input.GetKey("go_down"))
			Move_Option_Down();
		else if (e.key.code == m_input.GetKey("go_up"))
			Move_Option_Up();
		else if (e.key.code == m_input.GetKey("select"))
			Select(g);
		
		int dir = e.key.code == m_input.GetKey("go_right") ?  1 : 
				 (e.key.code == m_input.GetKey("go_left")  ? -1 : -2);
		
		if (dir != -2) {
			switch (current_option) {
			case 0:
				m_settings.rounds_left += dir;
				if (m_settings.rounds_left == 0)
					m_settings.rounds_left = 1;
				break;
			case 1: {
				int current = m_settings.round_type;
				
				m_settings.round_type += dir;
				if (m_settings.round_type >= m_roundtypes.size() || m_settings.round_type < 0)
					m_settings.round_type %= m_roundtypes.size();
				
				ReplaceRoundType(current, m_settings.round_type);
				break;
			} case 2:
				if (m_settings.round_type == 1) {
					m_settings.max_points += dir;
					if (m_settings.max_points == 0)
						m_settings.max_points = 1;
				}
				
				break;
			}
		}
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
	
	ReplaceNumber(0, m_settings.rounds_left);
	if (m_settings.round_type == 1) 
		ReplaceNumber(2, m_settings.max_points);
	else if (m_settings.round_type == 2) 
		ReplaceNumber(2, m_settings.max_seconds);
	else if (m_settings.round_type == 3) { 
		ReplaceNumber(2, m_settings.max_points);
		
		size_t pos = m_texts[2].getString().find("Clock");
		ReplaceNumber(2, m_settings.max_seconds, pos);
	}
}

void LobbyMenu::Render (DrawingEnviroment & drawEnv) {
	drawEnv.ClearWindow();
	
	for (auto& text : m_texts)
		drawEnv.AddToLayer(&text,0);
	
	drawEnv.DrawAll();
}

void LobbyMenu::ReplaceRoundType(int current, int next) {
	std::string str = m_texts[1].getString();
	std::string aux = m_roundtypes[current];
	
	size_t pos = str.find(aux);
	if (pos != std::string::npos)
		str = str.replace(pos, aux.size(), m_roundtypes[next]);
	m_texts[1].setString(str);
	m_texts[2].setString(m_descriptions[next]);
	
	CenterText(1);
	CenterText(2);
}

void LobbyMenu::CenterText (int index) {
	float prev_pos = m_texts[index].getPosition().y, prev_origin = m_texts[index].getOrigin().y;
	
	m_texts[index].setOrigin(utils::getCenter(m_texts[index].getLocalBounds()).x, prev_origin);
	m_texts[index].setPosition(winsize.x*0.5f, prev_pos);
}

void LobbyMenu::ReplaceNumber (int index, int new_number, size_t starting_pos) {
	std::string str = m_texts[index].getString();
	size_t b_pos = str.find_first_of("1234567890", starting_pos);
	size_t e_pos = str.find_first_not_of("1234567890", b_pos);
	if (b_pos != std::string::npos && e_pos != std::string::npos)
		str = str.replace(b_pos, e_pos-b_pos, std::to_string(new_number));
	m_texts[index].setString(str);
	CenterText(index);
}

std::string LobbyMenu::GetRandomMap ( ) {
	std::ifstream fin("../res/configuration-files/maps/allmaps.conf");
	std::vector<std::string> all_maps;
	
	std::string aux;
	while (getline(fin, aux))
		all_maps.push_back(aux);
	
	return all_maps.at(rand()%(all_maps.size()));
}

