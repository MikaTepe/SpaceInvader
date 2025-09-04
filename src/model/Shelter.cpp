#include "Shelter.hpp"
#include <string>
#include "Constants.hpp"

// Lädt einmalig die Schriftart und teilt sie zwischen allen Bunkern
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

// Konstruktor: platziert den Bunker und setzt Startwerte
Shelter::Shelter(const TextureManager& textureManager, float x, float y)
    : sprite(textureManager.get(TextureID::ShelterFull)),
      health(Constants::SHELTER_INITIAL_HEALTH),
      textureManagerRef(textureManager),
      healthText(getSharedFont(), std::to_string(health), Constants::SHELTER_HEALTH_FONT_SIZE)
{
    // Lebensaanzeige in Weiß
    healthText.setFillColor(sf::Color::White);

    // Ursprung des Sprites ins Zentrum setzen, damit alles clean ausgerichtet ist
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.f, sprite.getLocalBounds().size.y / 2.f});

    // Position und Skalierung setzen
    sprite.setPosition({x, y});
    sprite.setScale({Constants::SHELTER_SCALE, Constants::SHELTER_SCALE});

    // Starttextur anhand der Lebenspunkte setzen
    updateTexture();
}

// Reduziert die Lebenspunkte und aktualisiert die Textur
void Shelter::takeDamage() {
    if (health > 0) {
        health--;
        updateTexture();
    }
}

// Zeichnet den Bunker und seine Lebensanzeige, solange er nicht zerstört ist
void Shelter::draw(sf::RenderWindow& window) {
    if (health > 0) {
        window.draw(sprite);
        window.draw(healthText);
    }
}

// Gibt die Kollisionsbox des Bunkers zurück
sf::FloatRect Shelter::getBounds() const {
    return sprite.getGlobalBounds();
}

// Checkt, ob der Bunker zerstört wurde
bool Shelter::isDestroyed() const {
    return health <= 0;
}

// Aktualisiert Textur & Lebensanzeige basierend auf aktuellem Zustand
void Shelter::updateTexture() {
    if (health > 0) {
        // Starttextur: unbeschädigt
        TextureID id = TextureID::ShelterFull;

        // Falls schon Schaden genommen wurde -> andere Textur wählen
        if (health < Constants::SHELTER_INITIAL_HEALTH) {
            int damageLevel = Constants::SHELTER_DAMAGE_LEVELS -
                              (health - 1) / Constants::SHELTER_HEALTH_PER_DAMAGE_LEVEL;

            // Sicherheitscheck: Schaden nicht unter 1 oder über Maximum hinaus
            if (damageLevel < 1) damageLevel = 1;
            if (damageLevel > Constants::SHELTER_DAMAGE_LEVELS) damageLevel = Constants::SHELTER_DAMAGE_LEVELS;

            // Textur anhand des Schadenslevels setzen
            id = static_cast<TextureID>(static_cast<int>(TextureID::ShelterDamaged1) + (damageLevel - 1));
        }

        sprite.setTexture(textureManagerRef.get(id));
    }

    // Gesundheitsanzeige aktualisieren
    healthText.setString(std::to_string(health));
    sf::FloatRect textRect = healthText.getLocalBounds();

    // Text mittig über dem Bunker ausrichten
    healthText.setOrigin({
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    });

    float shelterTopEdge = sprite.getPosition().y - (sprite.getGlobalBounds().size.y / 2.f);
    healthText.setPosition({
        sprite.getPosition().x,
        shelterTopEdge - Constants::SHELTER_HEALTH_TEXT_Y_OFFSET
    });
}
