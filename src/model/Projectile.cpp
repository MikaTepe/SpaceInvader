#include "Projectile.hpp"

Projectile::Projectile(float x, float y, Type type) : type(type) {
    shape.setSize({5, 15});
    shape.setPosition({x, y});
    if (type == PlayerShot) {
        shape.setFillColor(sf::Color::White);
    } else {
        shape.setFillColor(sf::Color::Yellow);
    }
}

void Projectile::move() {
    if (type == PlayerShot) {
        shape.move({0, -speed});
    } else {
        shape.move({0, speed});
    }
}

sf::Vector2f Projectile::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}