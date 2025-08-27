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
    Game& gameRef;
    sf::Text gameOverText;
    sf::Text instructionText;
};

#endif //GAMEOVERSTATE_HPP
