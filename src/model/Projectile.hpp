#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../view/TextureManager.hpp"

class Projectile {
public:
    enum class Type { Player, Alien };

    Projectile(Type type, const TextureManager* textures, sf::Vector2f position, sf::Vector2f direction);

    void update(float deltaTime);

    const sf::Sprite& getSprite() const;
    sf::FloatRect getBounds() const;

    bool isActive = true;

private:
    void animate();

    const TextureManager* textureManager;
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;
    Type projectileType;

    std::vector<TextureID> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;
    sf::Time animationInterval;
};

#endif //PROJECTILE_HPP