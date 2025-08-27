#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "GameObject.hpp"
#include "Constants.hpp"

class PowerUp : public GameObject {
public:
    enum Type { ExtraLife, SpeedBoost };
    PowerUp(float x, float y, Type type);

    // Bewegt das Power-Up nach unten
    void move();

    // Getter für die Position
    sf::Vector2f getPosition() const override;
    // Getter für die Bounding Box
    sf::FloatRect getBounds() const override;

    sf::CircleShape shape;
    Type type;
};

#endif //POWERUP_HPP