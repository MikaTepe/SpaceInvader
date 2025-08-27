#include "PlayingState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"
#include <random>
#include <string>

PlayingState::PlayingState(Game& game)
    : gameRef(game),
      player(),
      alienDirection(1.0f),
      score(0),
      waveNumber(0),
      playerShootCooldown(sf::seconds(0.4f)),
      alienShootInterval(sf::seconds(1.0f)),
      scoreText(game.getFont(), "Score: 0", 24)
{
    srand(time(NULL));

    // HUD initialisieren
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f - scoreText.getLocalBounds().size.x / 2.f, 10.f});

    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape block({25.f, 15.f});
        block.setFillColor(sf::Color::Red);
        block.setPosition({Constants::WINDOW_WIDTH - 120.f + (i * 35.f), 15.f});
        lifeBlocks.push_back(block);
    }

    setupNewWave();
}

void PlayingState::setupNewWave() {
    waveNumber++;
    currentAlienSpeed = Constants::ALIEN_SPEED + (10.0f * (waveNumber - 1));
    aliens.clear();

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            int points = (i < 2) ? 20 : 10; // Obere zwei Reihen geben 20 Punkte
            aliens.emplace_back(100.0f + j * 60.0f, 50.0f + i * 40.0f, points);
        }
    }
}

void PlayingState::handleEvents(Game& game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (!player.isInvincible()) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                handlePlayerInput(keyPressed->code, true);
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                handlePlayerInput(keyReleased->code, false);
            }
        }
    }
}

void PlayingState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::Left) {
        player.isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Key::Right) {
        player.isMovingRight = isPressed;
    } else if (key == sf::Keyboard::Key::Space && isPressed) {
        if (playerShootClock.getElapsedTime() >= playerShootCooldown) {
            const auto& playerShape = player.getShape();
            playerProjectiles.emplace_back(playerShape.getPosition().x, playerShape.getPosition().y, 0.f, -1.f, sf::Color::Green);
            playerShootClock.restart();
        }
    }
}

void PlayingState::update(float deltaTime) {
    if (player.getLives() <= 0) {
        gameRef.changeStateToGameOver();
        return;
    }

    player.update(deltaTime);

    bool allAliensDefeated = true;
    bool changeDirection = false;
    for (auto& alien : aliens) {
        if (alien.isActive) {
            allAliensDefeated = false; // Mindestens ein Alien ist noch aktiv
            alien.move(alienDirection * currentAlienSpeed * deltaTime, 0);
            const auto& alienBounds = alien.getBounds();
            if (alienBounds.position.x < 0 || (alienBounds.position.x + alienBounds.size.x) > Constants::WINDOW_WIDTH) {
                changeDirection = true;
            }
        }
    }

    if (allAliensDefeated) {
        setupNewWave();
    }

    if (changeDirection) {
        alienDirection *= -1.0f;
        for (auto& alien : aliens) {
            alien.move(0, 20.0f);
        }
    }

    alienShoot();

    for (auto it = playerProjectiles.begin(); it != playerProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getShape().getPosition().y < 0) it = playerProjectiles.erase(it); else ++it;
    }
    for (auto it = alienProjectiles.begin(); it != alienProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getShape().getPosition().y > Constants::WINDOW_HEIGHT) it = alienProjectiles.erase(it); else ++it;
    }

    checkCollisions();
    updateHUD();
}

void PlayingState::updateHUD() {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f - scoreText.getLocalBounds().size.x / 2.f, 10.f});

    for(size_t i = 0; i < lifeBlocks.size(); ++i) {
        if (i < player.getLives()) {
            lifeBlocks[i].setFillColor(sf::Color::Red);
        } else {
            lifeBlocks[i].setFillColor(sf::Color(100, 100, 100)); // Grau für verlorene Leben
        }
    }
}

void PlayingState::alienShoot() {
    if (alienProjectiles.empty() && alienShootClock.getElapsedTime() >= alienShootInterval) {
        std::vector<int> activeAlienIndices;
        for (int i = 0; i < aliens.size(); ++i) {
            if (aliens[i].isActive) activeAlienIndices.push_back(i);
        }
        if (!activeAlienIndices.empty()) {
            int randomIndex = activeAlienIndices[rand() % activeAlienIndices.size()];
            const auto& alienShape = aliens[randomIndex].getShape();
            alienProjectiles.emplace_back(alienShape.getPosition().x, alienShape.getPosition().y, 0.f, 1.f, sf::Color::Red);
            alienShootClock.restart();
        }
    }
}

void PlayingState::checkCollisions() {
    playerProjectiles.erase(std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
        [this](Projectile& projectile) {
            for (auto& alien : aliens) {
                if (projectile.isActive && alien.isActive && projectile.getBounds().findIntersection(alien.getBounds())) {
                    projectile.isActive = false;
                    alien.isActive = false;
                    score += alien.scoreValue; // Punkte hinzufügen
                    return true;
                }
            }
            return false;
        }), playerProjectiles.end());

    alienProjectiles.erase(std::remove_if(alienProjectiles.begin(), alienProjectiles.end(),
        [this](Projectile& projectile) {
            if (projectile.isActive && !player.isInvincible() && projectile.getBounds().findIntersection(player.getBounds())) {
                player.handleHit();
                if (player.getLives() > 0) {
                    player.respawn();
                }
                return true;
            }
            return false;
        }), alienProjectiles.end());
}

void PlayingState::draw(sf::RenderWindow& window) {
    if (player.getLives() > 0) {
        window.draw(player.getShape());
    }
    for (const auto& alien : aliens) {
        if(alien.isActive) window.draw(alien.getShape());
    }
    for (const auto& projectile : playerProjectiles) {
        if(projectile.isActive) window.draw(projectile.getShape());
    }
    for (const auto& projectile : alienProjectiles) {
        if(projectile.isActive) window.draw(projectile.getShape());
    }

    // HUD zeichnen
    window.draw(scoreText);
    for(const auto& block : lifeBlocks) {
        window.draw(block);
    }
}
