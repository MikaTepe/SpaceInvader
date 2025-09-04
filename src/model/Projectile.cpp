#include "Projectile.hpp"
#include "Constants.hpp"



namespace {
    // Hilfsfunktion: Wählt die richtige Starttextur je nach Projektiltyp
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
      animationInterval(sf::seconds(Constants::PROJECTILE_ANIMATION_INTERVAL))
{
    // Animationsframes auswählen: Spieler- und Alienprojektile sidn unterschiedlich
    if (projectileType == Type::Player) {
        animationFrames = {
            TextureID::PlayerMissile1,
            TextureID::PlayerMissile2,
            TextureID::PlayerMissile3,
            TextureID::PlayerMissile4
        };
    } else {
        animationFrames = {
            TextureID::AlienMissile1,
            TextureID::AlienMissile2,
            TextureID::AlienMissile3,
            TextureID::AlienMissile4
        };
    }

    // Ursprung ins Zentrum setzen
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    // Startposition setzen (kommt von Spieler oder Alien)
    sprite.setPosition(position);

    // Projektile skalieren
    sprite.setScale({Constants::PROJECTILE_SCALE, Constants::PROJECTILE_SCALE});
}

// Update pro Frame – bewegt das Projektil & kümmert sich um die Animation
void Projectile::update(float deltaTime) {
    if (isActive) {
        // Bewegung entlang der Richtung (nach oben beim Spieler, nach unten bei Aliens)
        sprite.move(direction * speed * deltaTime);
        animate(); // kleine Frame-Animation
    }
}

// Frame-Animation für Projektil: durchläuft die Texturen in Schleife
void Projectile::animate() {
    if (animationClock.getElapsedTime() > animationInterval) {
        currentFrame = (currentFrame + 1) % animationFrames.size();
        sprite.setTexture(textureManager->get(animationFrames[currentFrame]));
        animationClock.restart();
    }
}

// Zugriff auf das Sprite, damit andere es zeichnen können
const sf::Sprite& Projectile::getSprite() const {
    return sprite;
}

// Gibt die aktuellen Kollisionsgrenzen des Projektils zurück
sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}
