#include "StartScreenState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"

StartScreenState::StartScreenState(Game& game)
    : gameRef(game),
      titleText(game.getFont(), "Space Invaders", 60),
      instructionText(game.getFont(), "Press Enter to Start", 30)
{
    // Konfiguriere den Titel-Text
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    titleText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f - 100.f});

    // Konfiguriere den Anweisungs-Text
    instructionText.setFillColor(sf::Color::White);
    sf::FloatRect instructionRect = instructionText.getLocalBounds();
    instructionText.setOrigin({instructionRect.position.x + instructionRect.size.x / 2.0f, instructionRect.position.y + instructionRect.size.y / 2.0f});
    instructionText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f});
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

void StartScreenState::update(float deltaTime) {
    // Auf dem Startbildschirm passiert nichts
}

void StartScreenState::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(instructionText);
}
