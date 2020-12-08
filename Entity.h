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
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	
	/// @brief Change where to search for textures.
	/// This method will probably be erased in the future; an Entity should stay the same along the Match.
	void SetKeyword(std::string new_key);
	
	/// @brief Fast collision checking method.
	/// @param another Check collision with this sprite.
	bool CollidesWith(const Entity &another);
	
	/// @brief Get the entity's m_sprite.
	sf::Sprite &GetSprite() { return m_sprite; }
	/// @brief Get the entity's m_speed.
	sf::Vector2f &GetSpeed() { return m_speed; }
	
	/// @brief Construct an Entity given its keyword.
	/** Every entity has its textures in textures.conf, to search an Entity's textures
		a keyword is needed. For example: to search the player textures, the "player"
		keyword must be given **/
	/// @param keyword String to search in textures.conf
	Entity(std::string keyword);
	virtual ~Entity() {}
protected:
	void LoadTextures();
	
	std::string m_key;
	sf::Vector2f m_speed;
	float m_topspeed;
	std::vector<sf::Texture> m_textures;
	sf::Sprite m_sprite;
};

#endif

