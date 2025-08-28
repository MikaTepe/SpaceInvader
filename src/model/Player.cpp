#include "Player.hpp"
#include "Constants.hpp"

Player::Player(const sf::Texture& texture) :
    sprite(texture),
    lives(3),
    invincible(false),
    invincibilityDuration(sf::seconds(2.f))
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
}

void Player::update(float deltaTime) {
    if (invincible) {
        if (invincibilityClock.getElapsedTime() >= invincibilityDuration) {
            invincible = false;
            sprite.setColor(sf::Color::White); // Farbe zurücksetzen
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
    sprite.move(movement);

    const auto& pos = sprite.getPosition();
    const auto halfWidth = sprite.getGlobalBounds().size.x / 2.f;
    if (pos.x < halfWidth) {
        sprite.setPosition({halfWidth, pos.y});
    }
    if (pos.x > Constants::WINDOW_WIDTH - halfWidth) {
        sprite.setPosition({Constants::WINDOW_WIDTH - halfWidth, pos.y});
    }
}

void Player::handleHit() {
    if (!invincible) {
        lives--;
        invincible = true;
        invincibilityClock.restart();
        sprite.setColor(sf::Color(255, 255, 255, 128)); // Leicht transparent
    }
}

void Player::respawn() {
    sprite.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT - 50.f});
    isMovingLeft = false;
    isMovingRight = false;
}

int Player::getLives() const { return lives; }
bool Player::isInvincible() const { return invincible; }
sf::Sprite& Player::getSprite() { return sprite; }
const sf::Sprite& Player::getSprite() const { return sprite; }
sf::FloatRect Player::getBounds() const { return sprite.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return sprite.getPosition(); }