#include "Flag.h"
#include "../../Utils/generalUtils.h"

Flag::Flag(sf::Vector2f pos, bool who) : 
	Item(pos, "suitcase"), m_trail(m_sprite, true),
	m_who(who)
{
	m_sprite.setTexture(m_textures[0]);
	
	m_dep.setTexture(m_textures[1]);
	m_dep.setColor(utils::loadPlayerColor(who));
	m_dep.scale(m_scale,m_scale);
	m_dep.setPosition(pos);
	m_trail.SetDep(m_dep);
}

void Flag::Render (DrawingEnviroment &drawEnv) {
	m_dep.setPosition(m_sprite.getPosition());
	
	if (m_speed.x != 0 || Owner() != -1) {
		m_sprite.setScale(m_dir*m_scale, m_scale);
		m_dep.setScale(m_dir*m_scale, m_scale);
	}
	
	if (Owner() != -1 || m_speed.x != 0 || m_speed.y != 0)
		m_trail.Render(drawEnv);
}

void Flag::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	target.draw(m_sprite,states);
	target.draw(m_dep,states);
}

void Flag::Update ( ) {
	Item::Update();
	if (Owner() != -1 || m_speed.x != 0 || m_speed.y != 0) { 
		auto globals = m_sprite.getGlobalBounds();
		
		m_trail.AddPosition(sf::Vector2f(globals.left, globals.top));
	} else m_trail.Clear();
}

void Flag::SetOwner (int owner, const sf::Vector2f &release_speed) {
	prev_owner = Owner();
	Item::SetOwner(owner, release_speed);
}

int Flag::WasCaptured (int base_index) {
	bool was_stolen, taken_home;
	was_stolen = (m_who != prev_owner);
	taken_home = (prev_owner == base_index);
	
	if (was_stolen && taken_home && prev_owner != -1)  {
		SetUsing(false);
		return prev_owner;
	}
	
	return -1;
}

