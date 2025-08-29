#include "Alien.hpp"
#include "Constants.hpp"

Alien::Alien(const sf::Texture& texture, float startX, float startY, int score)
    : scoreValue(score), sprite(texture) {
    sprite.setPosition({startX, startY});
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    sprite.setScale({Constants::ALIEN_SCALE, Constants::ALIEN_SCALE});
}

void Alien::move(float x, float y) {
    sprite.move({x, y});
}

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