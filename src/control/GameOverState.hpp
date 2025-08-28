#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "GameState.hpp"
#include <SFML/Graphics/Text.hpp>

class GameOverState : public GameState {
public:
    explicit GameOverState(Game& game);

    void handleEvents(Game& game) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text instructionText;
};

#endif //GAMEOVERSTATE_HPP
