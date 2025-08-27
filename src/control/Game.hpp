#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../view/GameView.hpp"
#include "../model/Player.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include "../model/PowerUp.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void checkCollisions();

    GameView view;
    Player player;
    std::vector<Alien> aliens;
    std::vector<Projectile> projectiles;
    std::vector<PowerUp> powerUps;
    float alienDirection;
};