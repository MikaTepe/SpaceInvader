#include "Alien.hpp"

bool Alien::moveDown = false;

Alien::Alien(float x, float y) {
    shape.setSize({40, 30});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({x, y});
}

void Alien::move(float x, float y) {
    shape.move({x, y});
}

sf::Vector2f Alien::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Alien::getBounds() const {
    return shape.getGlobalBounds();
}