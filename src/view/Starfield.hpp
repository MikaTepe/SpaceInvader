#ifndef STARFIELD_HPP
#define STARFIELD_HPP

#include <SFML/Graphics.hpp>
#include <vector>

// Struktur, die einen einzelnen Stern im Hintergrund darstellt
struct Star {
    sf::RectangleShape shape;
    sf::Clock twinkleClock;
    sf::Time twinkleDuration;
    float speed;
};

class Starfield {
public:
    Starfield();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Star> stars;
    int numStars;
};

#endif //STARFIELD_HPP
