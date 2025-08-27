#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile {
public:
    // Der Konstruktor akzeptiert jetzt eine Farbe, um Spieler- und Alien-Schüsse zu unterscheiden
    Projectile(float startX, float startY, float dirX, float dirY, sf::Color color);
    void update(float deltaTime);
    const sf::RectangleShape& getShape() const;
    sf::FloatRect getBounds() const;
    bool isActive = true;

private:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed;
};

#endif //PROJECTILE_HPP
