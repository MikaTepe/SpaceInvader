#include "Shelter.hpp"
#include <string>
#include "Constants.hpp"

sf::Font& Shelter::getSharedFont() {
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (font.openFromFile(Constants::FONT_PATH)) {
            fontLoaded = true;
        }
    }
    return font;
}

Shelter::Shelter(const TextureManager& textureManager, float x, float y)
    : sprite(textureManager.get(TextureID::ShelterFull)),
      health(Constants::SHELTER_INITIAL_HEALTH),
      textureManagerRef(textureManager),
      healthText(getSharedFont(), std::to_string(health), Constants::SHELTER_HEALTH_FONT_SIZE)
{
    healthText.setFillColor(sf::Color::White);

    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    sprite.setPosition({x, y});
    sprite.setScale({Constants::SHELTER_SCALE, Constants::SHELTER_SCALE});

    updateTexture();
}

void Shelter::takeDamage() {
    if (health > 0) {
        health--;
        updateTexture();
    }
}

void Shelter::draw(sf::RenderWindow& window) {
    if (health > 0) {
        window.draw(sprite);
        window.draw(healthText);
    }
}

sf::FloatRect Shelter::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Shelter::isDestroyed() const {
    return health <= 0;
}

void Shelter::updateTexture() {
    if (health > 0) {
        TextureID id = TextureID::ShelterFull;
        if (health < Constants::SHELTER_INITIAL_HEALTH) {
            int damageLevel = Constants::SHELTER_DAMAGE_LEVELS - (health - 1) / Constants::SHELTER_HEALTH_PER_DAMAGE_LEVEL;
            if (damageLevel < 1) damageLevel = 1;
            if (damageLevel > Constants::SHELTER_DAMAGE_LEVELS) damageLevel = Constants::SHELTER_DAMAGE_LEVELS;
            id = static_cast<TextureID>(static_cast<int>(TextureID::ShelterDamaged1) + (damageLevel - 1));
        }
        sprite.setTexture(textureManagerRef.get(id));
    }

    healthText.setString(std::to_string(health));
    sf::FloatRect textRect = healthText.getLocalBounds();

    healthText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});

    float shelterTopEdge = sprite.getPosition().y - (sprite.getGlobalBounds().size.y / 2.f);
    healthText.setPosition({sprite.getPosition().x, shelterTopEdge - Constants::SHELTER_HEALTH_TEXT_Y_OFFSET});
}