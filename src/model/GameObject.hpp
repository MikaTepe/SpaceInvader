#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject {
public:
    explicit GameObject(const sf::Texture& texture) : sprite(texture) {
    }
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;

    sf::Sprite& getSprite() { return sprite; }

    // Gibt jetzt eine Kopie statt einer ungültigen Referenz zurück.
    sf::Vector2f getPosition() const { return sprite.getPosition(); }

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    bool isActive = true;

protected:
    sf::Sprite sprite;
    sf::Vector2f velocity;
};

#endif //GAMEOBJECT_HPP