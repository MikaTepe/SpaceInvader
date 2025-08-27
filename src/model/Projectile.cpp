#include "Projectile.hpp"
#include "Constants.hpp"

// Der Konstruktor setzt jetzt die übergebene Farbe
Projectile::Projectile(float startX, float startY, float dirX, float dirY, sf::Color color) {
    shape.setSize({5.f, 15.f});
    shape.setFillColor(color); // Farbe wird hier gesetzt
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setPosition({startX, startY});
    direction = {dirX, dirY};
    speed = Constants::PROJECTILE_SPEED;
}

void Projectile::update(float deltaTime) {
    shape.move(direction * speed * deltaTime);
}

const sf::RectangleShape& Projectile::getShape() const {
    return shape;
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}
