#include "Game.hpp"
#include "StartScreenState.hpp"
#include "PlayingState.hpp"
#include "GameOverState.hpp"
#include "../model/Constants.hpp"
#include <iostream>
#include <fstream>

Game::Game() :
    window(sf::VideoMode({static_cast<unsigned int>(Constants::WINDOW_WIDTH), static_cast<unsigned int>(Constants::WINDOW_HEIGHT)}), "Space Invaders"),
    font(std::make_unique<sf::Font>()),
    textureManager(),
    starfield(),
    highScore(0),
    lastScore(0)
{
    window.setFramerateLimit(Constants::FRAME_RATE_LIMIT);
    font->openFromFile(Constants::FONT_PATH);

    loadHighScore();
    currentState = std::make_unique<StartScreenState>(*this);
}

void Game::loadHighScore() {
    std::ifstream file(Constants::HIGHSCORE_FILE);
    if (file.is_open()) {
        file >> highScore;
    }
}

void Game::saveHighScore() {
    std::ofstream file(Constants::HIGHSCORE_FILE);
    if (file.is_open()) {
        file << highScore;
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    if (currentState) {
        currentState->handleEvents(*this);
    }
}

void Game::update(float deltaTime) {
    starfield.update(deltaTime);
    if (currentState) {
        currentState->update(deltaTime);
    }
}

void Game::render() {
    window.clear();
    starfield.draw(window);
    if (currentState) {
        currentState->draw(window);
    }
    window.display();
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}

void Game::changeStateToStartScreen() {
    changeState(std::make_unique<StartScreenState>(*this));
}

void Game::changeStateToPlaying() {
    changeState(std::make_unique<PlayingState>(*this));
}

void Game::changeStateToGameOver(int finalScore) {
    lastScore = finalScore;
    if (lastScore > highScore) {
        highScore = lastScore;
        saveHighScore();
    }
    changeState(std::make_unique<GameOverState>(*this));
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

const sf::Font& Game::getFont() const {
    return *font;
}

const TextureManager& Game::getTextureManager() const {
    return textureManager;
}

int Game::getHighScore() const {
    return highScore;
}

int Game::getLastScore() const {
    return lastScore;
}
