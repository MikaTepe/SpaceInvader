#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class TextureID {
    Player,
    InvaderL1,
    InvaderL2,
    InvaderM1,
    InvaderM2,
    PlayerExplosion,
    InvaderExplosion,
    PlayerMissile1,
    PlayerMissile2,
    PlayerMissile3,
    PlayerMissile4,
    AlienMissile1,
    AlienMissile2,
    AlienMissile3,
    AlienMissile4,
    ShelterFull,
    ShelterDamaged1,
    ShelterDamaged2,
    ShelterDamaged3,
    ShelterDamaged4,
    ShelterDamaged5,
    ShelterDamaged6,
    ShelterDamaged7,
    ShelterDamaged8,
    ShelterDamaged9
};

class TextureManager {
public:
    TextureManager();
    const sf::Texture& get(TextureID id) const;

private:
    void loadTexture(TextureID id, const std::string& filename);
    std::map<TextureID, sf::Texture> textures;
};

#endif //TEXTUREMANAGER_HPP