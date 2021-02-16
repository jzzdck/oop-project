#include "Match.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "../../Game.h"
#include "../../Entity/Player.h"
#include "../Menu/Menu_Principal.h"
#include "../../Graphics/DrawingEnviroment.h"
#include <algorithm>
#include "../../Utils/generalUtils.h"
using namespace std;

Match::Match(MatchSettings m, float width, float height) :
	Scene(width, height), m_pause(false),
	m_entities(width, height, m.map_name), 
	m_camera(width, height), 
	m_gamehud({width, height}, m.map_name, m),
	m_settings(m),
	m_pmenu(width,height,&m_pause,&m_camera)
{
	m_gamehud.Init(m_entities.GetPlayersInfos());
}

void Match::ProcessEvent(sf::Event& e, Game& g) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Escape)
			m_pause = !m_pause;
		if(e.key.code == sf::Keyboard::Add)
			m_camera.In_De_creaseZoom(0.05);
		if(e.key.code == sf::Keyboard::Subtract)
			m_camera.In_De_creaseZoom(-0.05);
	} else if (e.type == sf::Event::LostFocus)
		m_pause = true;
	
	if (m_pause)
		m_pmenu.ProcessEvent(e,g);
	else
		m_entities.ProcessPlayersEvents(e, g);
}

void Match::Update (Game& g) {
	if (m_pause) {
		m_pmenu.Update(g);
		return;
	}
	
	int someone_won = CurrentRoundEnded(m_entities.GetRoundPoints());
	if (someone_won != -1) {
		if (someone_won == -2) {
			std::cout << "Nobody won!" << std::endl;
			// DRAW, continue match:
			g.SetScene(new Match(m_settings, win_width, win_height));
			return;
		}
		
		UpdateGameState(someone_won, g);
	}
	
	m_entities.Update(m_gameclock.getElapsedTime());
	m_gamehud.Update(m_entities.GetPlayersInfos(), m_gameclock.getElapsedTime().asSeconds());
	m_camera.Update(m_entities.GetCameraInfo());
	if (utils::randf() < 0.0005f)
		m_entities.SpawnSomethingAtRandom();
}

void Match::Render (DrawingEnviroment& drawEnv) {
	drawEnv.ClearWindow({158, 207, 222});
	m_camera.SetToWindow(*drawEnv.getWin());
	m_gamehud.Render(drawEnv, m_camera.GetZoom());
	m_entities.Render(drawEnv);
	
	if(m_pause)
		m_pmenu.Render(drawEnv);
	drawEnv.DrawAll();
}

Match::~Match() {
	
}

int Match::CurrentRoundEnded ( const std::vector<int> &round_state ) {
	auto winning_player = std::max_element(round_state.begin(), round_state.end());
	
	float total_time = m_gameclock.getElapsedTime().asSeconds();
	int draw = std::count(round_state.begin(), round_state.end(), *winning_player); 
	
	bool ended_by_time = total_time > m_settings.max_seconds;
	bool ended_by_points = *winning_player >= m_settings.max_points;
	
	if (ended_by_time || ended_by_points) {
		if ((m_settings.round_type == 1 && ended_by_points) ||
			(m_settings.round_type == 2 && ended_by_time)   ||
			(m_settings.round_type == 3))
		{
			if (draw == 1)
				return winning_player - round_state.begin();
			else 
				return -2;
		}
	}
	
	return -1;
}

void Match::UpdateGameState (int someone_won, Game & g) {
	int &winner_points = m_settings.rounds_won[someone_won];
	winner_points++;
	m_settings.rounds_left--;
	
	std::cout << "Player " << someone_won 
			  << " won " << winner_points << " time(s)" << std::endl;
	
	if (m_settings.random_rounds)
		m_settings.Randomize();
	
	if (m_settings.rounds_left > 0)
		g.SetScene(new Match(m_settings, win_width, win_height));
	else {
		auto it = std::max_element(m_settings.rounds_won.begin(),
								   m_settings.rounds_won.end());
		
		int draw = std::count(m_settings.rounds_won.begin(),
							  m_settings.rounds_won.end(), *it);
		
		if (draw == 1)
			std::cout << "Player " << it - m_settings.rounds_won.begin() 
					  << " won the match. " << std::endl;
		else
			std::cout << "The match was drawn." << std::endl;
		
		g.SetScene(new Menu_Principal(win_width, win_height));
	}
}
