#include "Player.hpp"

Player::Player() {
    shape.setSize({50, 30});
    shape.setFillColor(sf::Color::Green);
    // Erstelle einen sf::Vector2f mit {}
    shape.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
}

void Player::moveLeft() {
    if (shape.getPosition().x > 0) {
        // Erstelle einen sf::Vector2f mit {}
        shape.move({-speed, 0.f});
    }
}

void Player::moveRight() {
    if (shape.getPosition().x < Constants::WINDOW_WIDTH - shape.getSize().x) {
        // Erstelle einen sf::Vector2f mit {}
        shape.move({speed, 0.f});
    }
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}