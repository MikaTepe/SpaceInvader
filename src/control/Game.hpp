#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <SFML/System/Clock.hpp>
#include "../model/Player.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include "../model/PowerUp.hpp"
#include "../view/GameView.hpp" // Wichtig: Inkludiert die korrekte GameView-Definition

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void spawnAliens();

    GameView view;
    Player player;
    std::vector<Alien> aliens;
    std::vector<Projectile> projectiles;
    std::vector<PowerUp> powerUps;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    sf::Clock shootClock;
    sf::Vector2f alienDirection;
};

#endif //GAME_HPP