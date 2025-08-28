#include "StartScreenState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"
#include <string>

StartScreenState::StartScreenState(Game& game)
    : titleText(game.getFont(), "Space Invaders", 60),
      instructionText(game.getFont(), "Press Enter to Start", 30),
      highScoreText(game.getFont(), "High Score: " + std::to_string(game.getHighScore()), 24)
{
    // Titel-Text
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    titleText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f - 100.f});

    // Anweisungs-Text
    instructionText.setFillColor(sf::Color::White);
    sf::FloatRect instructionRect = instructionText.getLocalBounds();
    instructionText.setOrigin({instructionRect.position.x + instructionRect.size.x / 2.0f, instructionRect.position.y + instructionRect.size.y / 2.0f});
    instructionText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f});

    // Highscore-Text
    highScoreText.setFillColor(sf::Color::Yellow);
    sf::FloatRect hsRect = highScoreText.getLocalBounds();
    highScoreText.setOrigin({hsRect.position.x + hsRect.size.x / 2.0f, hsRect.position.y + hsRect.size.y / 2.0f});
    highScoreText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f + 50.f});
}

void StartScreenState::handleEvents(Game& game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                game.changeStateToPlaying();
            }
        }
    }
}

void StartScreenState::update(float deltaTime) {}

void StartScreenState::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(instructionText);
    window.draw(highScoreText);
}
