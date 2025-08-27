#include "Game.hpp"
#include "StartScreenState.hpp"
#include "PlayingState.hpp"
#include "GameOverState.hpp"
#include "../model/Constants.hpp"
#include <iostream>

Game::Game() :
    window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Space Invaders"),
    font(std::make_unique<sf::Font>())
{
    window.setFramerateLimit(60);

    if (!font->openFromFile("assets/fonts/DejaVuSansMono.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        window.close();
        return;
    }

    currentState = std::make_unique<StartScreenState>(*this);
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
    if (currentState) {
        currentState->update(deltaTime);
    }
}

void Game::render() {
    window.clear();
    if (currentState) {
        currentState->draw(window);
    }
    window.display();
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}

void Game::changeStateToPlaying() {
    //Übergibt 'this' an den Konstruktor von PlayingState
    changeState(std::make_unique<PlayingState>(*this));
}

void Game::changeStateToGameOver() {
    changeState(std::make_unique<GameOverState>(*this));
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

const sf::Font& Game::getFont() const {
    return *font;
}
