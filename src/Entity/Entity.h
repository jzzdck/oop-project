#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../Escena/Match/Plataform/Plataform.h"

class Entity: public sf::Drawable {
public:
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	
	bool CollidesWith(const sf::Sprite &another);
	virtual void ApplyGravity(float gravity) { m_speed.y += gravity; }
	virtual void ApplyResponse(const sf::Vector2f &vec);
	
	sf::Sprite &GetSprite() { return m_sprite; }
	sf::Vector2f &GetSpeed() { return m_speed; }
	sf::Vector2f &GetInitPos() { return m_initpos; }
	float GetFacing() const { return m_dir; } 
	bool IsUsed() const { return in_use; }
	
	void SetSpeed(sf::Vector2f new_speed) { m_speed = new_speed; }
	void SetPlatform(Plataform* relative_to) { m_platform = relative_to; }
	
	Entity(sf::Vector2f pos, std::string keyword);
	virtual ~Entity() = default;
protected:
	std::string m_key;
	
	sf::Vector2f m_speed, m_initpos;
	float m_topspeed;
	
	float m_dir, m_scale = 2.f;
	std::vector<sf::Texture> m_textures;
	sf::Sprite m_sprite;
	Plataform * m_platform = nullptr;
	bool in_use = true;
};

#endif

