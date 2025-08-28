#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(const sf::Texture& texture)
    : GameObject(texture),
      speed(Constants::PLAYER_SPEED),
      lives(3),
      invincible(false),
      invincibilityDuration(sf::seconds(1.5f))
{
    sprite.setOrigin({sprite.getGlobalBounds().size.x / 2.f, sprite.getGlobalBounds().size.y / 2.f});

    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
}

void Player::update(float deltaTime) {
    if (invincible && invincibilityClock.getElapsedTime() > invincibilityDuration) {
        invincible = false;
        sprite.setColor(sf::Color::White);
    }

    if (!invincible) {
        velocity.x = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && (sprite.getPosition().x > sprite.getGlobalBounds().size.x / 2.f)) {
            velocity.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && (sprite.getPosition().x < Constants::WINDOW_WIDTH - sprite.getGlobalBounds().size.x / 2.f)) {
            velocity.x += speed;
        }

        sprite.move(velocity * deltaTime);
    }
}

void Player::handleHit() {
    if (!invincible) {
        lives--;
        invincible = true;
        invincibilityClock.restart();
        sprite.setColor(sf::Color(255, 255, 255, 128));
    }
}

void Player::respawn() {
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    invincible = true;
    invincibilityClock.restart();
    sprite.setColor(sf::Color(255, 255, 255, 128));
}

bool Player::isInvincible() const {
    return invincible;
}

int Player::getLives() const {
    return lives;
}