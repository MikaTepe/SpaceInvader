#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    explicit Player(const sf::Texture& texture);
    void update(float deltaTime);

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    void handleHit();
    void respawn();
    int getLives() const;
    bool isInvincible() const;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isActive = true;

private:
    sf::Sprite sprite;
    int lives;
    bool invincible;
    sf::Clock invincibilityClock;
    sf::Time invincibilityDuration;
};

#endif //PLAYER_HPP
