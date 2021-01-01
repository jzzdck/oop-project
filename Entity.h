#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Game;

/// @brief Entity is the highest hierarchy level for any entity in the game. 
class Entity {
public:
	virtual void Update();
	virtual void Draw(sf::RenderWindow &win) = 0;
	
	/// @brief Fast collision checking method.
	/// @param another Check collision with this sprite.
	bool CollidesWith(const Entity &another);
	/// @brief Apply gravity from World.
	void ApplyGravity(float gravity) { m_speed.y += gravity; }
	virtual void ApplyResponse(const sf::Vector2f &vec);
	
	/// @brief Get the entity's m_sprite.
	sf::Sprite &GetSprite() { return m_sprite; }
	/// @brief Get the entity's m_speed.
	sf::Vector2f &GetSpeed() { return m_speed; }
	void SetSpeed(sf::Vector2f new_speed) { m_speed = new_speed; }
	
	/// @brief Construct an Entity given its keyword.
	/** Every entity has its textures in textures.conf, to search an Entity's textures
		a keyword is needed. For example: to search the player textures, the "player"
		keyword must be given **/
	/// @param keyword String to search in textures.conf
	/// @param pos Intial entity position
	Entity(sf::Vector2f pos, std::string keyword);
	virtual ~Entity() {}
protected:
	std::string m_key;
	
	sf::Vector2f m_speed;
	float m_topspeed;
	
	std::vector<sf::Texture> m_textures;
	sf::Sprite m_sprite;
};

#endif

