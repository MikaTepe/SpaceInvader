#include "Player.hpp

Player::Player() {
    // Initialisiert die 'shape' aus der GameObject-Basisklasse
    shape.setSize({50.f, 30.f});
    shape.setFillColor(sf::Color::Green);

    // Wir übergeben jetzt einen Vector2f, anstatt zwei einzelne floats.
    shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f}); // Zentriert die Position

    shape.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
}

void Player::update(float deltaTime) {
    // Die Bewegungslogik bleibt gleich
    if (isMovingLeft && shape.getPosition().x > 0 + shape.getSize().x / 2.f) {
        shape.move({-Constants::PLAYER_SPEED * deltaTime, 0.f});
    }
    if (isMovingRight && shape.getPosition().x < Constants::WINDOW_WIDTH - shape.getSize().x / 2.f) {
        shape.move({Constants::PLAYER_SPEED * deltaTime, 0.f});
    }
}