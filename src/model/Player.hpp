#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Constants.hpp"

class Player : public GameObject {
public:
    Player();

    // Bewegt den Spieler nach links
    void moveLeft();
    // Bewegt den Spieler nach rechts
    void moveRight();

    // Getter für die Position
    sf::Vector2f getPosition() const override;
    // Getter für die Bounding Box
    sf::FloatRect getBounds() const override;

    sf::RectangleShape shape;
    int lives = 3;

private:
    float speed = Constants::PLAYER_SPEED;
};

#endif //PLAYER_HPP