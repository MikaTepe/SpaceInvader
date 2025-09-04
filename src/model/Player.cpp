#include "Player.hpp"

Player::Player(const sf::Texture& texture)
    : GameObject(texture),
      speed(Constants::PLAYER_SPEED),
      lives(Constants::PLAYER_INITIAL_LIVES),
      invincible(false),
      invincibilityDuration(sf::seconds(Constants::PLAYER_INVINCIBILITY_DURATION))
{
    // Textur setzen & Spieler skalieren
    sprite.setTexture(texture);
    sprite.setScale({Constants::PLAYER_SCALE, Constants::PLAYER_SCALE});

    // Ursprung in die Mitte setzen, damit Bewegungen und Trefferzonen clean sind
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    // Spieler startet mittig unten
    sprite.setPosition({
        Constants::WINDOW_WIDTH / 2.f,
        Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET
    });
}

// Update pro Frame
void Player::update(float) {
    // Wenn die Unverwundbarkeit abgelaufen ist, wieder normal einfärben
    if (invincible && invincibilityClock.getElapsedTime() >= invincibilityDuration) {
        invincible = false;
        sprite.setColor(sf::Color::White);
    }
}

// Wird aufgerufen, wenn der Spieler getroffen wird
void Player::handleHit() {
    if (!invincible) {
        lives--;                          // Leben verlieren
        invincible = true;                // Kurzzeitig unverwundbar
        invincibilityClock.restart();     // Timer starten
        sprite.setColor(Constants::PLAYER_HIT_COLOR);
    }
}

// Respawn an Startposition, z.B. nach Treffer
void Player::respawn() {
    // Zurück in die Mitte unten
    sprite.setPosition({
        Constants::WINDOW_WIDTH / 2.f,
        Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET
    });

    // Direkt nach Respawn: Unverwundbarkeit aktivieren
    invincible = true;
    invincibilityClock.restart();
    sprite.setColor(Constants::PLAYER_HIT_COLOR);
}

// Spieler nach links bewegen
void Player::moveLeft(float deltaTime) {
    if (sprite.getPosition().x > getBounds().size.x / 2.f) {
        sprite.move({-speed * deltaTime, 0});
    }
}

// Spieler nach rechts bewegen
void Player::moveRight(float deltaTime) {
    if (sprite.getPosition().x < Constants::WINDOW_WIDTH - getBounds().size.x / 2.f) {
        sprite.move({speed * deltaTime, 0});
    }
}

// Check: Ist der Spieler momentan unverwundbar?
bool Player::isInvincible() const {
    return invincible;
}

// Anzahl der verbleibenden Leben zurückgeben
int Player::getLives() const {
    return lives;
}