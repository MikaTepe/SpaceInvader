#ifndef PLAYINGSTATE_HPP
#define PLAYINGSTATE_HPP

#include "GameState.hpp"
#include "../model/Player.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include "../model/PowerUp.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>

class Game;

class PlayingState : public GameState {
public:
    explicit PlayingState(Game& game);

    void handleEvents(Game& game) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void checkCollisions();
    void alienShoot();
    void setupNewWave(); // Für neue Wellen
    void updateHUD();    // Für die Aktualisierung der Anzeige

    Game& gameRef;
    Player player;
    std::vector<Alien> aliens;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> alienProjectiles;
    std::vector<PowerUp> powerUps;

    float alienDirection;
    float currentAlienSpeed;
    int score;
    int waveNumber;

    // Timer
    sf::Clock playerShootClock;
    sf::Time playerShootCooldown;
    sf::Clock alienShootClock;
    sf::Time alienShootInterval;

    // HUD Elemente
    sf::Text scoreText;
    std::vector<sf::RectangleShape> lifeBlocks;
};

#endif //PLAYINGSTATE_HPP
