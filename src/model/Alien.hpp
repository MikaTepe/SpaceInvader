#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <SFML/Graphics.hpp>

class Alien {
public:
    Alien(const sf::Texture& texture, float startX, float startY, int score);
    void move(float x, float y);

    // Gibt eine veränderbare Referenz zurück, um die Textur zu wechseln
    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    bool isActive = true;
    int scoreValue;

private:
    sf::Sprite sprite;
};

#endif //ALIEN_HPP
