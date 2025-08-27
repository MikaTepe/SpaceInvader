#include "Projectile.hpp"

// Der Konstruktor nimmt die Startposition (x, y) und die Richtung (dirX, dirY) entgegen
Projectile::Projectile(float startX, float startY, float dirX, float dirY) : direction(dirX, dirY) {
    shape.setSize({5.f, 15.f});
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f});
    shape.setPosition({startX, startY});
}

void Projectile::update(float deltaTime) {
    // Bewegt die Form basierend auf Richtung, Geschwindigkeit und der Zeit seit dem letzten Frame
    sf::Vector2f movement = direction * Constants::PROJECTILE_SPEED;
    shape.move(movement * deltaTime);

    if (shape.getPosition().y < 0 || shape.getPosition().y > Constants::WINDOW_HEIGHT) {
        isActive = false;
    }
}