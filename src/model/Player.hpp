#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Constants.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Player : public GameObject {
public:
    explicit Player(const sf::Texture& texture);

    void update(float deltaTime) override; // Funktioniert jetzt korrekt
    void handleHit();
    void respawn();

    bool isInvincible() const;
    int getLives() const;

private:
    float speed;
    int lives;
    bool invincible;
    sf::Clock invincibilityClock;
    sf::Time invincibilityDuration;
};

#endif //PLAYER_HPP