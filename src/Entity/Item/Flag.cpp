#include "Flag.h"
#include "../../Utils/generalUtils.h"

Flag::Flag(sf::Vector2f pos, bool who) : 
	Item(pos, "suitcase"), m_trail(m_sprite, true),
	m_who(who)
{
	m_sprite.setTexture(m_textures[0]);
	
	m_dep.setTexture(m_textures[1]);
	m_dep.setColor(utils::loadPlayerColor(who));
	m_dep.setOrigin(m_dep.getGlobalBounds().width, 0);
	m_dep.scale(2,2);
	m_dep.setPosition(pos);
	m_trail.SetDep(m_dep);
}

void Flag::Render (DrawingEnviroment &drawEnv) {
	m_dep.setPosition(m_sprite.getPosition());
	
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

