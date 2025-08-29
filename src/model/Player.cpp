#include "Player.hpp"

Player::Player(const sf::Texture& texture)
    : GameObject(texture),
      speed(Constants::PLAYER_SPEED),
      lives(3),
      invincible(false),
      invincibilityDuration(sf::seconds(2.f)) {
    sprite.setTexture(texture);
    sprite.setScale({2.f, 2.f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
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
        // NEU: Färbt den Spieler grau, um den Treffer zu signalisieren.
        sprite.setColor(sf::Color(128, 128, 128, 180)); // Grau mit leichter Transparenz
    }
}

void Player::respawn() {
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    invincible = true;
    invincibilityClock.restart();
    // Sorgt dafür, dass der Spieler auch nach dem Respawn kurz grau ist.
    sprite.setColor(sf::Color(128, 128, 128, 180));
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