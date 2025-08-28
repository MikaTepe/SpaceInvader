#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(const sf::Texture& texture, sf::Vector2f position);

    bool isFinished() const;
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Clock lifetimeClock;
    sf::Time duration;
};

#endif //EXPLOSION_HPP
