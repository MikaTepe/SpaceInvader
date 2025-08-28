#include "Explosion.hpp"

Explosion::Explosion(const sf::Texture& texture, sf::Vector2f position)
    : sprite(texture), duration(sf::seconds(0.5f))
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition(position);
    lifetimeClock.restart();
}

bool Explosion::isFinished() const {
    return lifetimeClock.getElapsedTime() >= duration;
}

void Explosion::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}