#include "Alien.hpp"

Alien::Alien(float startX, float startY) {
    // Initialisiert die 'shape' aus der GameObject-Basisklasse
    shape.setSize({40.f, 30.f});
    shape.setFillColor(sf::Color::Red);

    // Die beiden float-Werte werden zu einem Vector2f zusammengefasst.
    shape.setOrigin({shape.getSize().x / 2.f, shape.getSize().y / 2.f});

    shape.setPosition({startX, startY});
}

void Alien::move(float x, float y) {
    // Bewegt das Alien um den angegebenen Versatz
    shape.move({x, y});
}