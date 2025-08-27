#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class Game {
public:
    Game();
    void run();

    void changeState(std::unique_ptr<GameState> newState);
    void changeStateToPlaying();
    void changeStateToGameOver();

    sf::RenderWindow& getWindow();
    const sf::Font& getFont() const;

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<sf::Font> font;
};

#endif //GAME_HPP
