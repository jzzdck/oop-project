#include "Game.h"
#include "Menu.h"
#include "Match.h"

Game::Game (float width, float height, std::string window_name) :
	win_width(width), win_height(height),
	m_window(sf::VideoMode(width, height), window_name),
	m_current_scene(new Menu(width, height))
{
	m_window.setFramerateLimit(60);
	m_next_scene = nullptr;
}

Game::~Game() {
	delete m_current_scene;
	delete m_next_scene;
}

void Game::Run( ) {
	while(m_window.isOpen()) {
		ProcessEvents();
		Update();
		Draw();
		
		if (m_next_scene) {
			delete m_current_scene;
			m_current_scene = m_next_scene;
			
			m_next_scene = nullptr;
		}
	}
}

void Game::Update ( ) {
	m_current_scene->Update(*this);
}

void Game::Draw ( ) {
	m_current_scene->Draw(m_window);
}

void Game::SetScene (Escena * next_scene) {
	m_next_scene = next_scene;
	
}

void Game::ProcessEvents ( ) {
	sf::Event e;
	while(m_window.pollEvent(e)) {
		if(e.type == sf::Event::Closed)
			m_window.close();
	
	}
}

