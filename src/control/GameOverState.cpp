#include "GameOverState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"

GameOverState::GameOverState(Game& game)
    : gameRef(game),
      gameOverText(game.getFont(), "GAME OVER", 70),
      instructionText(game.getFont(), "Press Enter to Restart", 30)
{
    // Konfiguriere Game-Over-Text
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect titleRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    gameOverText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f - 100.f});

    // Konfiguriere Anweisungs-Text
    instructionText.setFillColor(sf::Color::White);
    sf::FloatRect instructionRect = instructionText.getLocalBounds();
    instructionText.setOrigin({instructionRect.position.x + instructionRect.size.x / 2.0f, instructionRect.position.y + instructionRect.size.y / 2.0f});
    instructionText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f});
}

void GameOverState::handleEvents(Game& game) {
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

void GameOverState::update(float deltaTime) {
    // Nichts zu aktualisieren
}

void GameOverState::draw(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(instructionText);
}
