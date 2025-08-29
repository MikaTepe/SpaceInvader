#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(const sf::Texture& texture, sf::Vector2f position, float scale = 1.0f);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isFinished() const;

private:
    sf::Sprite sprite;
    sf::Clock clock;
    bool finished = false;
};

#endif //EXPLOSION_HPP