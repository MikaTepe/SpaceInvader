#include "Alien.hpp"

Alien::Alien(const sf::Texture& texture, float startX, float startY, int score)
    : scoreValue(score), sprite(texture) {
    sprite.setPosition({startX, startY});
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    // Skaliert die Invader auf 1.5-fache Größe
    sprite.setScale({1.5f, 1.5f});
}

void Alien::move(float x, float y) {
    sprite.move({x, y});
}

sf::Sprite& Alien::getSprite() {
    return sprite;
}

// Gibt eine konstante Referenz zurück
const sf::Sprite& Alien::getSprite() const {
    return sprite;
}

sf::FloatRect Alien::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Alien::getPosition() const {
    return sprite.getPosition();
}