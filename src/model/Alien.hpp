#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <SFML/Graphics.hpp>

class Alien {
public:
    Alien(float startX, float startY, int score); // Konstruktor nimmt jetzt einen Punktewert an
    void move(float x, float y);
    const sf::RectangleShape& getShape() const;
    sf::FloatRect getBounds() const;

    bool isActive = true;
    int scoreValue; // Punktewert für diesen Alien-Typ

private:
    sf::RectangleShape shape;
};

#endif //ALIEN_HPP
