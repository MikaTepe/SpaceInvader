#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float deltaTime);

    // Gibt eine veränderbare Referenz zurück, um die Farbe ändern zu können
    sf::RectangleShape& getShape();
    const sf::RectangleShape& getShape() const;

    sf::FloatRect getBounds() const;

    // Neue Methoden für die Lebens- und Trefferlogik
    void handleHit();
    void respawn();
    int getLives() const;
    bool isInvincible() const;

    // Steuerungsvariablen
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isActive = true;

private:
    sf::RectangleShape shape;
    int lives;
    bool invincible;
    sf::Clock invincibilityClock;
    sf::Time invincibilityDuration;
};

#endif //PLAYER_HPP
