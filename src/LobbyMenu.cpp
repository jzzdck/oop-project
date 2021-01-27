#include "LobbyMenu.h"
#include "Escena/Menu/Menu_Principal.h"
#include "Game.h"
#include "Utils/generalUtils.h"
#include "Escena/Match/Match.h"

LobbyMenu::LobbyMenu(float width, float height) : 
	Menu(width, height, "lobby"), winsize(sf::Vector2f(width, height)) 
{
	m_roundtypes = { 
		"RANDOM", "POINTS", "TIMED", "BOTH" 
	};
	
	m_descriptions = { 
		"Every round is different \nand decided at random.", // random
		
		"The first player to score << 7 >> points\nwins the round.", // points
		
		"The player who scored more points\nwhen the clock stops wins the round.\n" 
		"Clock will stop at: << 60 >> seconds.", // timed
		
		"A combination of the previous types,\n" // both
		"The player who scores 7 points \n"
		"OR scores more points when\nthe clock stops, wins the round.\n" // both
		"Clock will stop at: 60 seconds" // both
	};
	
	ReplaceRoundType(m_settings.round_type, 0);
	current_option = 3;
	m_texts[current_option].setStyle(sf::Text::Italic|sf::Text::Bold);
}

void LobbyMenu::Select (Game & g) {
	switch (current_option) 
	{
	case 3:
		if (m_settings.round_type != 0)
			m_settings.random_rounds = false;
		else
			m_settings.Randomize();
		
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
		
		if (e.key.code == m_input.GetKey("go_up"))
			Move_Option_Up();
		if (e.key.code == m_input.GetKey("go_down"))
			Move_Option_Down();
		
		if (e.key.code == m_input.GetKey("go_right")) {
			if (current_option == 1) {
				int current = m_settings.round_type;
				
				m_settings.round_type++;
				if (m_settings.round_type >= m_roundtypes.size())
					m_settings.round_type = 0;
				
				ReplaceRoundType(current, m_settings.round_type);
			} else if (current_option == 0)
				m_settings.rounds_left++;
			else if (current_option == 2) {
				if (m_settings.round_type == 1)
					m_settings.max_points++;
			}
		}
		
		if (e.key.code == m_input.GetKey("go_left")) {
			if (current_option == 1) {
				int current = m_settings.round_type;
				
				m_settings.round_type--;
				if (m_settings.round_type < 0)
					m_settings.round_type = m_roundtypes.size()-1;
				
				ReplaceRoundType(current, m_settings.round_type);
			} else if (current_option == 0 && m_settings.rounds_left > 1)
				m_settings.rounds_left--;
			else if (current_option == 2) {
				if (m_settings.round_type == 1 && m_settings.max_points > 1)
					m_settings.max_points--;
			}
		}
		
		if (e.key.code == m_input.GetKey("select"))
			Select(g);
	}
}

void LobbyMenu::Update (Game & g) {	
	HighlightCurrentOption();
	
	if (current_option == 2 && m_settings.round_type == 2) {
		if (m_input.KeyState("go_left") && m_settings.max_seconds > 15)
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

void LobbyMenu::Draw (sf::RenderWindow & win) {
	win.clear({0, 0, 0});
	
	for(const auto &text : m_texts)
		win.draw(text);
	
	win.display();
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

