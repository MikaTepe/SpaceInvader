#include "Alien.hpp"

Alien::Alien(float startX, float startY, int score) : scoreValue(score) {
    shape.setSize({40.f, 20.f});
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setPosition({startX, startY});
}

void Alien::move(float x, float y) {
    shape.move({x, y});
}

const sf::RectangleShape& Alien::getShape() const {
    return shape;
}

sf::FloatRect Alien::getBounds() const {
    return shape.getGlobalBounds();
}
