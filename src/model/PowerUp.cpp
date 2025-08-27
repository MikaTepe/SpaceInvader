#include "PowerUp.hpp"

PowerUp::PowerUp(float x, float y, Type type) : type(type) {
    shape.setRadius(15);
    shape.setPosition({x, y});
    if (type == ExtraLife) {
        shape.setFillColor(sf::Color::Magenta);
    } else {
        shape.setFillColor(sf::Color::Cyan);
    }
}

void PowerUp::move() {
    shape.move({0, Constants::POWERUP_SPEED});
}

sf::Vector2f PowerUp::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect PowerUp::getBounds() const {
    return shape.getGlobalBounds();
}