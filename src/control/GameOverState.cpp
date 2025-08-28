#include "GameOverState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"
#include <string>

GameOverState::GameOverState(Game& game)
    : gameOverText(game.getFont(), "GAME OVER", 70),
      scoreText(game.getFont(), "Your Score: " + std::to_string(game.getLastScore()), 30),
      highScoreText(game.getFont(), "High Score: " + std::to_string(game.getHighScore()), 30),
      instructionText(game.getFont(), "Press Enter to Restart\nPress M for Menu", 24)
{
    // Game Over Text
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect goRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin({goRect.position.x + goRect.size.x / 2.0f, goRect.position.y + goRect.size.y / 2.0f});
    gameOverText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f - 150.f});

    // Score Text
    scoreText.setFillColor(sf::Color::White);
    sf::FloatRect scoreRect = scoreText.getLocalBounds();
    scoreText.setOrigin({scoreRect.position.x + scoreRect.size.x / 2.0f, scoreRect.position.y + scoreRect.size.y / 2.0f});
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f - 50.f});

    // Highscore Text
    highScoreText.setFillColor(sf::Color::Yellow);
    sf::FloatRect hsRect = highScoreText.getLocalBounds();
    highScoreText.setOrigin({hsRect.position.x + hsRect.size.x / 2.0f, hsRect.position.y + hsRect.size.y / 2.0f});
    highScoreText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f});

    // Anweisungs-Text
    instructionText.setFillColor(sf::Color(180, 180, 180));
    sf::FloatRect instRect = instructionText.getLocalBounds();
    instructionText.setOrigin({instRect.position.x + instRect.size.x / 2.0f, instRect.position.y + instRect.size.y / 2.0f});
    instructionText.setPosition({Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f + 100.f});
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
            if (keyPressed->code == sf::Keyboard::Key::M) {
                game.changeStateToStartScreen();
            }
        }
    }
}

void GameOverState::update(float deltaTime) {}

void GameOverState::draw(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(instructionText);
}