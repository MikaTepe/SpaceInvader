#include "Projectile.hpp"
#include "Constants.hpp"

Projectile::Projectile(Type type, const TextureManager* textures, sf::Vector2f position, sf::Vector2f direction)
    : textureManager(textures),
      sprite(textureManager->get(type == Type::Player ? TextureID::PlayerMissile1 : TextureID::AlienMissile1)),
      projectileType(type),
      currentFrame(0),
      animationInterval(sf::seconds(0.2f))
{
    this->direction = direction;
    this->speed = Constants::PROJECTILE_SPEED;

    if (projectileType == Type::Player) {
        animationFrames = { TextureID::PlayerMissile1, TextureID::PlayerMissile2, TextureID::PlayerMissile3, TextureID::PlayerMissile4 };
    } else {
        animationFrames = { TextureID::AlienMissile1, TextureID::AlienMissile2, TextureID::AlienMissile3, TextureID::AlienMissile4 };
    }

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition(position);
}

void Projectile::update(float deltaTime) {
    sprite.move(direction * speed * deltaTime);
    animate();
}

void Projectile::animate() {
    if (animationClock.getElapsedTime() > animationInterval) {
        currentFrame = (currentFrame + 1) % animationFrames.size();
        sprite.setTexture(textureManager->get(animationFrames[currentFrame]));
        animationClock.restart();
    }
}

const sf::Sprite& Projectile::getSprite() const {
    return sprite;
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}