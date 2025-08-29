#include "TextureManager.hpp"
#include <iostream>
#include <string>

TextureManager::TextureManager() {
    loadTexture(TextureID::Player, "assets/sprites/player.png");
    loadTexture(TextureID::PlayerExplosion, "assets/sprites/playerExplosionA.png");
    loadTexture(TextureID::InvaderExplosion, "assets/sprites/invaderExplosion.png");

    // Lade Alien-Animationen
    loadTexture(TextureID::InvaderL1, "assets/sprites/invaders/invaderL1.png");
    loadTexture(TextureID::InvaderL2, "assets/sprites/invaders/invaderL2.png");
    loadTexture(TextureID::InvaderM1, "assets/sprites/invaders/invaderM1.png");
    loadTexture(TextureID::InvaderM2, "assets/sprites/invaders/invaderM2.png");

    // Lade Spieler-Projektil-Animationen
    loadTexture(TextureID::PlayerMissile1, "assets/sprites/playermissle/missile_1.png");
    loadTexture(TextureID::PlayerMissile2, "assets/sprites/playermissle/missile_2.png");
    loadTexture(TextureID::PlayerMissile3, "assets/sprites/playermissle/missile_3.png");
    loadTexture(TextureID::PlayerMissile4, "assets/sprites/playermissle/missile_4.png");

    // Lade Alien-Projektil-Animationen
    loadTexture(TextureID::AlienMissile1, "assets/sprites/alienmissle/ProjectileA_1.png");
    loadTexture(TextureID::AlienMissile2, "assets/sprites/alienmissle/ProjectileA_2.png");
    loadTexture(TextureID::AlienMissile3, "assets/sprites/alienmissle/ProjectileA_3.png");
    loadTexture(TextureID::AlienMissile4, "assets/sprites/alienmissle/ProjectileA_4.png");

    // Lade Shelter-Texturen
    loadTexture(TextureID::ShelterFull, "assets/sprites/shelter/shelter_full.png");
    for (int i = 1; i <= 9; ++i) {
        TextureID id = static_cast<TextureID>(static_cast<int>(TextureID::ShelterDamaged1) + i - 1);
        loadTexture(id, "assets/sprites/shelter/shelterDamaged_" + std::to_string(i) + ".png");
    }
}

void TextureManager::loadTexture(TextureID id, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading texture file: " << filename << std::endl;
        return;
    }
    textures[id] = texture;
}

const sf::Texture& TextureManager::get(TextureID id) const {
    return textures.at(id);
}