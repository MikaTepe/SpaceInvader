#include "Alien.hpp"

Alien::Alien(const sf::Texture& texture, float startX, float startY, int score)
    : scoreValue(score), sprite(texture)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition({startX, startY});
}

void Alien::move(float x, float y) {
    sprite.move({x, y});
}

// Gibt eine veränderbare Referenz auf das Sprite zurück
sf::Sprite& Alien::getSprite() {
    return sprite;
}

const sf::Sprite& Alien::getSprite() const {
    return sprite;
}

sf::FloatRect Alien::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Alien::getPosition() const {
    return sprite.getPosition();
}
