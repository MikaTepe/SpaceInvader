#include "Player.hpp"

Player::Player(const sf::Texture& texture)
    : GameObject(texture),
      speed(Constants::PLAYER_SPEED),
      lives(Constants::PLAYER_INITIAL_LIVES),
      invincible(false),
      invincibilityDuration(sf::seconds(Constants::PLAYER_INVINCIBILITY_DURATION)) {
    sprite.setTexture(texture);
    sprite.setScale({Constants::PLAYER_SCALE, Constants::PLAYER_SCALE});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET});
}

void Player::update(float) {
    if (invincible && invincibilityClock.getElapsedTime() >= invincibilityDuration) {
        invincible = false;
        sprite.setColor(sf::Color::White);
    }
}

void Player::handleHit() {
    if (!invincible) {
        lives--;
        invincible = true;
        invincibilityClock.restart();
        sprite.setColor(Constants::PLAYER_HIT_COLOR);
    }
}

void Player::respawn() {
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET});
    invincible = true;
    invincibilityClock.restart();
    sprite.setColor(Constants::PLAYER_HIT_COLOR);
}

void Player::moveLeft(float deltaTime) {
    if (sprite.getPosition().x > getBounds().size.x / 2.f) {
        sprite.move({-speed * deltaTime, 0});
    }
}

void Player::moveRight(float deltaTime) {
    if (sprite.getPosition().x < Constants::WINDOW_WIDTH - getBounds().size.x / 2.f) {
        sprite.move({speed * deltaTime, 0});
    }
}

bool Player::isInvincible() const {
    return invincible;
}

int Player::getLives() const {
    return lives;
}