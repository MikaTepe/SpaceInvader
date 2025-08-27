#pragma once

#include "GameObject.hpp"
#include "Constants.hpp"

class Projectile : public GameObject {
public:
    // Konstruktor, der Startposition und Richtung entgegennimmt
    Projectile(float startX, float startY, float dirX, float dirY);

    // Update-Methode für die Bewegung des Geschosses
    void update(float deltaTime);

private:
    // Richtung, in die sich das Geschoss bewegt
    sf::Vector2f direction;
};