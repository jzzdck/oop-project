#include "Game.h"
#include "Scene/Menu/Menu_Principal.h"

Game::Game(float width, float height, std::string window_name) :
	win_width(width), win_height(height), 
	m_window(sf::VideoMode(width, height), window_name),
	m_current_scene(new Menu_Principal(width, height)),
	m_drawEnv(&m_window,10)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(1024, 768, desktop.bitsPerPixel), window_name);
	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(60);
}

Game::~Game() {
	delete m_current_scene;
	delete m_next_scene;
}

void Game::Run() {
	while(m_window.isOpen()) {
		ProcessEvents();
		Update();
		Render();
		
		if (m_next_scene) {
			delete m_current_scene;
			m_current_scene = m_next_scene;
			m_window.setView( m_window.getDefaultView() );
			m_next_scene = nullptr;
		}
	}
}

void Game::Update() {
	m_current_scene->Update(*this);
}

void Game::Render() 
{
	m_current_scene->Render(m_drawEnv);
}

void Game::SetScene (Scene * next_scene) {
	m_next_scene = next_scene;
}

void Game::ProcessEvents() {
	sf::Event e;
	while (m_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			m_window.close();
		else 
			m_current_scene->ProcessEvent(e,*this);
	}
}

void Game::Close() {
	m_window.close();
}
