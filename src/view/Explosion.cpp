#include "Explosion.hpp"

Explosion::Explosion(const sf::Texture& texture, sf::Vector2f position, float scale)
    : sprite(texture), finished(false) // Initialisiere 'sprite' hier
{
    // Die restliche Konfiguration erfolgt nach der Erstellung.
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});
    sprite.setPosition(position);
    sprite.setScale({scale, scale});
}

void Explosion::update(float deltaTime) {

    if (clock.getElapsedTime().asSeconds() > 0.5f) { // Beispielzeit
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