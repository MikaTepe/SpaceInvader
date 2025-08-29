#include "Explosion.hpp"
#include "../model/Constants.hpp"

Explosion::Explosion(const sf::Texture& texture, sf::Vector2f position, float scale)
    : sprite(texture), finished(false)
{
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});
    sprite.setPosition(position);
    sprite.setScale({scale, scale});
}

void Explosion::update(float deltaTime) {
    if (clock.getElapsedTime().asSeconds() > Constants::EXPLOSION_DURATION) {
        finished = true;
    }
}

void Explosion::draw(sf::RenderWindow& window) {
    if (!finished) {
        window.draw(sprite);
    }
}

bool Explosion::isFinished() const {
    return finished;
}