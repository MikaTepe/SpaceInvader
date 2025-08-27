#pragma once

#include "GameObject.hpp"
#include "Constants.hpp"

class Player : public GameObject {
public:
    Player();
    void update(float deltaTime);

    bool isMovingLeft = false;
    bool isMovingRight = false;
};