#include "PlayerUpdater.h"

PlayerUpdater::PlayerUpdater(const sf::Vector2f &winsize) 
	: EntityArray(winsize) 
{ 
	m_respawners.assign(2, 0.00f);
}

void PlayerUpdater::UpdateRegardingTo(PlayerInfo &info, Player * player, World &world) {
	HealthData &h = player->GetHealthData();
	auto &respawner = m_respawners[player->GetIndex()];
	Update(player, world);
	
	if (world.IsUnbounded(player))
		h.current_health = -1000.f;

	if (!h.is_alive) {
		info.weapon_index = -1;
		
		if (respawner == 0.00f)
			respawner = m_gameclock.getElapsedTime().asSeconds();
		
		float can_respawn = m_gameclock.getElapsedTime().asSeconds() - respawner;
		if (can_respawn >= 1.5f) {
			player->SetPosition(player->GetInitPos());
			player->SetSpeed({0, 0});
			h.current_health = 1000.f;
			h.is_alive = true;
			respawner = 0.00f;
		}
	}
}

void PlayerUpdater::ProcessPlayerEvents (PlayerInfo &info, Player * player, sf::Event & e) {
	player->ProcessEvents(e);
}

