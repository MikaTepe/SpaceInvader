#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "GameObject.hpp"
#include "Constants.hpp"

class Projectile : public GameObject {
public:
    enum Type { PlayerShot, AlienShot };
    Projectile(float x, float y, Type type);

    // Bewegt das Geschoss
    void move();

    // Getter für die Position
    sf::Vector2f getPosition() const override;
    // Getter für die Bounding Box
    sf::FloatRect getBounds() const override;

    sf::RectangleShape shape;
    Type type;

private:
    float speed = Constants::PROJECTILE_SPEED;
};

#endif //PROJECTILE_HPP