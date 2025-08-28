#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "../view/Starfield.hpp"
#include "../view/TextureManager.hpp"

class Game {
public:
    Game();
    void run();

    void changeState(std::unique_ptr<GameState> newState);
    void changeStateToStartScreen();
    void changeStateToPlaying();
    void changeStateToGameOver(int finalScore);

    sf::RenderWindow& getWindow();
    const sf::Font& getFont() const;
    const TextureManager& getTextureManager() const;
    int getHighScore() const;
    int getLastScore() const;

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void loadHighScore();
    void saveHighScore();

    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<sf::Font> font;

    TextureManager textureManager;
    Starfield starfield;

    int highScore;
    int lastScore;
};

#endif //GAME_HPP