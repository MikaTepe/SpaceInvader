#include "Player.hpp"
#include "Constants.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(const sf::Texture& texture)
    : GameObject(texture), speed(Constants::PLAYER_SPEED), lives(3), invincible(false) {
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    sprite.setScale({2.0f, 2.0f});
}

void Player::update(float deltaTime) {
    if (!invincible) {
        sf::Vector2f position = sprite.getPosition();

        // Bewegung nach links
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && position.x > sprite.getGlobalBounds().size.x / 2.f) {
            position.x -= speed * deltaTime;
        }
        // Bewegung nach rechts
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && position.x < Constants::WINDOW_WIDTH - sprite.getGlobalBounds().size.x / 2.f) {
            position.x += speed * deltaTime;
        }
        sprite.setPosition(position);
    }

    // Unverwundbarkeits-Timer
    if (invincible && invincibilityClock.getElapsedTime().asSeconds() > 2.f) {
        invincible = false;
        sprite.setColor(sf::Color::White);
    }
}

void Player::handleHit() {
    if (!invincible) {
        lives--;
        invincible = true;
        invincibilityClock.restart();
        sprite.setColor(sf::Color(255, 255, 255, 128)); // Macht den Spieler halb-transparent
    }
}

void Player::respawn() {
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    invincible = true;
    invincibilityClock.restart();
    sprite.setColor(sf::Color(255, 255, 255, 128));
}

int Player::getLives() const {
    return lives;
}

bool Player::isInvincible() const {
    return invincible;
}