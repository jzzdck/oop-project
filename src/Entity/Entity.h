#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../EntitiesFacade/Platform.h"

class Entity : public sf::Drawable {
public:
	virtual void Update();
	virtual void Render() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	
	bool CollidesWith(Entity *another);
	virtual void ApplyForce(const sf::Vector2f &force) { m_accel += force; }
	virtual void ApplyResponse(const sf::Vector2f &vec);
	bool HasPlatform() { return m_platform; }
	sf::Rect<float> GetBounds() const { return m_sprite.getGlobalBounds(); }
	sf::Vector2f GetSpeed() const { return m_speed; }
	sf::Vector2f GetInitPos() const { return m_initpos; }
	float GetFacing() const { return m_dir; } 
	bool IsUsed() const { return in_use; }
	
	void SetPosition(const sf::Vector2f &new_pos) { m_sprite.setPosition(new_pos); }
	void SetSpeed(const sf::Vector2f &new_speed) { m_speed = new_speed; }
	void SetPlatform(const Platform* relative_to) { m_platform = relative_to; }
	
	Entity(sf::Vector2f pos, std::string keyword);
	virtual ~Entity() = default;
protected:
	sf::Vector2f m_speed, m_accel;
	
	float m_dir = 1.f, m_scale = 2.f;
	sf::Sprite m_sprite;
	std::vector<sf::Texture> m_textures;
	const Platform * m_platform = nullptr;
	bool in_use = true;
private:
	sf::Vector2f m_initpos;
	std::string m_key;
};

#endif

