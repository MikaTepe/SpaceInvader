#ifndef PLAYINGSTATE_HPP
#define PLAYINGSTATE_HPP

#include "GameState.hpp"
#include "SoundManager.hpp"
#include "../view/Explosion.hpp"
#include "../model/Player.hpp"
#include "../model/Shelter.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include <vector>
#include <SFML/System/Clock.hpp>
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
    void setupNewWave();
    void setupShelters();
    void updateHUD();
    void updateAlienAnimation();

    Game& gameRef;
    Player player;
    std::vector<Alien> aliens;
    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> alienProjectiles;
    std::vector<Explosion> explosions;
    std::vector<Shelter> shelters;

    float alienDirection;
    float currentAlienSpeed;
    int score;
    int waveNumber;

    sf::Clock playerShootClock;
    sf::Time playerShootCooldown;
    sf::Clock alienShootClock;
    sf::Time alienShootInterval;
    sf::Clock animationClock;
    sf::Time animationInterval;
    bool isFirstFrame;

    sf::Text scoreText;
    std::vector<sf::RectangleShape> lifeBlocks;
    SoundManager soundManager;
};

#endif //PLAYINGSTATE_HPP