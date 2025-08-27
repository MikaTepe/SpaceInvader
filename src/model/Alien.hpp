#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "GameObject.hpp"
#include "Constants.hpp"

class Alien : public GameObject {
public:
    Alien(float x, float y);

    // Bewegt das Alien
    void move(float x, float y);

    // Getter für die Position
    sf::Vector2f getPosition() const override;
    // Getter für die Bounding Box
    sf::FloatRect getBounds() const override;

    sf::RectangleShape shape;
    static bool moveDown;
};

#endif //ALIEN_HPP