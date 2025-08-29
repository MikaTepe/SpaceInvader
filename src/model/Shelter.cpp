#include "Shelter.hpp"
#include <string>

sf::Font& Shelter::getSharedFont() {
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (font.openFromFile("assets/fonts/DejaVuSansMono.ttf")) {
            fontLoaded = true;
        }
    }
    return font;
}

Shelter::Shelter(const TextureManager& textureManager, float x, float y)
    : sprite(textureManager.get(TextureID::ShelterFull)),
      health(30),
      textureManagerRef(textureManager),
      healthText(getSharedFont(), std::to_string(health), 12)
{
    healthText.setFillColor(sf::Color::White);

    // getLocalBounds() gibt die Originalgröße der Textur an
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    // Die Position und Skalierung werden nach dem Setzen des Ursprungs angewendet.
    sprite.setPosition({x, y});
    sprite.setScale({2.0f, 2.0f});

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
        if (health < 30) {
            int damageLevel = 9 - (health - 1) / 3;
            if (damageLevel < 1) damageLevel = 1;
            if (damageLevel > 9) damageLevel = 9;
            id = static_cast<TextureID>(static_cast<int>(TextureID::ShelterDamaged1) + (damageLevel - 1));
        }
        sprite.setTexture(textureManagerRef.get(id));
    }

    healthText.setString(std::to_string(health));
    sf::FloatRect textRect = healthText.getLocalBounds();

    // Zentriert den Ursprung des Textes
    healthText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});

    // Positioniert den Text mittig über dem Shelter
    float shelterTopEdge = sprite.getPosition().y - (sprite.getGlobalBounds().size.y / 2.f);
    healthText.setPosition({sprite.getPosition().x, shelterTopEdge - 15.f});
}