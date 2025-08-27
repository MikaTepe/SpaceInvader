#pragma once

#include "GameObject.hpp"
#include "Constants.hpp"
#include "Player.hpp" // Nötig für applyEffect

class PowerUp : public GameObject {
public:
    // Konstruktor, der die Startposition festlegt
    PowerUp(float startX, float startY);

    // Bewegt das Power-Up nach unten
    void update(float deltaTime);

    // Wendet den Effekt auf den Spieler an (Beispiel)
    void applyEffect(Player& player);
};