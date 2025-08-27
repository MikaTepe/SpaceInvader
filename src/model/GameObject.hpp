#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject {
public:
    // Virtueller Destruktor für Basisklassen
    virtual ~GameObject() = default;

    // Getter für die Position
    virtual sf::Vector2f getPosition() const = 0;
    // Getter für die Bounding Box (für Kollisionen)
    virtual sf::FloatRect getBounds() const = 0;

    bool isActive = true; // Ist das Objekt aktiv im Spiel?
};

#endif //GAMEOBJECT_HPP