#ifndef SHELTER_HPP
#define SHELTER_HPP

#include <SFML/Graphics.hpp>
#include "../view/TextureManager.hpp"

class Shelter {
public:
    Shelter(const TextureManager& textureManager, float x, float y);

    void takeDamage();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isDestroyed() const;

private:
    static sf::Font& getSharedFont();
    void updateTexture();

    sf::Sprite sprite;
    int health;
    const TextureManager& textureManagerRef;
    sf::Text healthText;
};

#endif // SHELTER_HPP