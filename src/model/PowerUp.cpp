#include "PowerUp.hpp"

PowerUp::PowerUp(float startX, float startY) {
    shape.setSize({20.f, 20.f});
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f}); // Korrekter Aufruf
    shape.setPosition({startX, startY});
}

void PowerUp::update(float deltaTime) {
    // Power-Up bewegt sich nach unten
    shape.move({0.f, Constants::POWERUP_SPEED * deltaTime});

    // Deaktivieren, wenn es aus dem Bildschirm ist
    if (shape.getPosition().y > Constants::WINDOW_HEIGHT) {
        isActive = false;
    }
}

void PowerUp::applyEffect(Player& player) {
    // z.B. player.activateShield(), muss nochmal schauen was es wird.
}