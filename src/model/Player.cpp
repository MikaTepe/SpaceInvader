#include "Player.hpp"
#include "Constants.hpp"

Player::Player() : lives(3), invincible(false), invincibilityDuration(sf::seconds(2.f)) {
    shape.setSize({60.f, 20.f});
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
}

void Player::update(float deltaTime) {
    if (invincible) {
        if (invincibilityClock.getElapsedTime() >= invincibilityDuration) {
            invincible = false;
            shape.setFillColor(sf::Color::Green);
        }
        return;
    }

    sf::Vector2f movement(0.f, 0.f);
    if (isMovingLeft) {
        movement.x -= Constants::PLAYER_SPEED * deltaTime;
    }
    if (isMovingRight) {
        movement.x += Constants::PLAYER_SPEED * deltaTime;
    }
    shape.move(movement);

    const auto& pos = shape.getPosition();
    const auto halfWidth = shape.getSize().x / 2.f;
    if (pos.x < halfWidth) {
        shape.setPosition({halfWidth, pos.y});
    }
    if (pos.x > Constants::WINDOW_WIDTH - halfWidth) {
        shape.setPosition({Constants::WINDOW_WIDTH - halfWidth, pos.y});
    }
}

void Player::handleHit() {
    if (!invincible) {
        lives--;
        invincible = true;
        invincibilityClock.restart();
        shape.setFillColor(sf::Color(128, 128, 128, 128));
    }
}

void Player::respawn() {
    shape.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    isMovingLeft = false;
    isMovingRight = false;
}

int Player::getLives() const {
    return lives;
}

bool Player::isInvincible() const {
    return invincible;
}

sf::RectangleShape& Player::getShape() {
    return shape;
}

const sf::RectangleShape& Player::getShape() const {
    return shape;
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}
