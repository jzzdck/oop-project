#include "HUD.h"
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"

HUD::HUD (int player_index) : m_playercolor("player-color")
{
	m_dir = player_index ? 1.f : -1.f;
	FileManager s("PlayerHUD.conf", "HUD");
	
	m_relative_percentage = utils::getXY(s["relative_percentage"]);
	m_texture.loadFromFile("../res/healthbar.png");
	m_hud.setTexture(m_texture);
	m_playercolor.SetColor(utils::loadPlayerColor(player_index));
}

void HUD::Render (DrawingEnviroment &drawEnv, float zoom_level) {
	m_pos = m_relative_percentage;
	if (m_dir == -1.f)
		m_pos.x += 0.9f;
	
	m_playercolor.Render(m_pos, drawEnv, zoom_level, m_dir);
	m_ammobar.Render(m_pos, drawEnv, zoom_level, m_dir);
	m_healthbar.Render(m_pos, drawEnv, zoom_level, m_dir);
	
	m_hud.setTexture(m_texture);
	m_hud.setPosition(utils::getFixedPos(drawEnv.getWin(), m_pos, {0,0}));
	m_hud.setScale(m_dir*3*zoom_level, 3*zoom_level);
}

void HUD::draw(sf::RenderTarget& target,sf::RenderStates states) const {
	target.draw(m_hud,states);
}

void HUD::Update (const PlayerInfo &info) {
	m_healthbar.Update(info);
	m_ammobar.Update(info);
}
