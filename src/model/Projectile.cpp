#include "Projectile.hpp"
#include "Constants.hpp"

namespace {
    TextureID getInitialTextureId(Projectile::Type type) {
        return (type == Projectile::Type::Player) ? TextureID::PlayerMissile1 : TextureID::AlienMissile1;
    }
}

Projectile::Projectile(Type type, const TextureManager* textures, sf::Vector2f position, sf::Vector2f direction)
    : textureManager(textures),
      sprite(textureManager->get(getInitialTextureId(type))),
      direction(direction),
      speed(Constants::PROJECTILE_SPEED),
      projectileType(type),
      currentFrame(0),
      animationInterval(sf::seconds(Constants::PROJECTILE_ANIMATION_INTERVAL)) {

    if (projectileType == Type::Player) {
        animationFrames = {TextureID::PlayerMissile1, TextureID::PlayerMissile2, TextureID::PlayerMissile3, TextureID::PlayerMissile4};
    } else {
        animationFrames = {TextureID::AlienMissile1, TextureID::AlienMissile2, TextureID::AlienMissile3, TextureID::AlienMissile4};
    }

    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});
    sprite.setPosition(position);
    sprite.setScale({Constants::PROJECTILE_SCALE, Constants::PROJECTILE_SCALE});
}

void Projectile::update(float deltaTime) {
    if (isActive) {
        sprite.move(direction * speed * deltaTime);
        animate();
    }
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