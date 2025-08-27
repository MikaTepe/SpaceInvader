#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default;

    bool isActive = true;

    virtual sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    // Diese öffentliche Methode gibt eine Referenz auf das shape-Objekt zurück,
    // damit die GameView es zeichnen kann, ohne direkt darauf zuzugreifen.
    const sf::RectangleShape& getShape() const {
        return shape;
    }

protected:
    sf::RectangleShape shape;
};