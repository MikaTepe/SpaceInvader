#include "PowerUp.hpp"

PowerUp::PowerUp(const sf::Texture& texture, float startX, float startY)
    : GameObject(texture)
{
    sprite.setOrigin({sprite.getGlobalBounds().size.x / 2.f, sprite.getGlobalBounds().size.y / 2.f});
    sprite.setPosition({startX, startY});
}

void PowerUp::update(float deltaTime) {
    sprite.move({0.f, Constants::POWERUP_SPEED * deltaTime});

    if (sprite.getPosition().y > Constants::WINDOW_HEIGHT) {
        isActive = false;
    }
}