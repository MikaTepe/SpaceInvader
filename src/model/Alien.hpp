#pragma once

#include "GameObject.hpp"

class Alien : public GameObject {
public:
    // Konstruktor, der die Startposition des Aliens festlegt
    Alien(float startX, float startY);

    // Methode, um das Alien zu bewegen
    void move(float x, float y);
};