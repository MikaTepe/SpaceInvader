#include "PlayingState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"
#include "../view/TextureManager.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <random>
#include <string>

PlayingState::PlayingState(Game& game)
    : gameRef(game),
      player(game.getTextureManager().get(TextureID::Player)),
      alienDirection(1.0f),
      score(0),
      waveNumber(0),
      playerShootCooldown(sf::seconds(0.4f)),
      alienShootInterval(sf::seconds(1.0f)),
      animationInterval(sf::seconds(1.0f)),
      isFirstFrame(true),
      scoreText(game.getFont(), "Score: 0", 24)
{
    srand(time(NULL));
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f - scoreText.getLocalBounds().size.x / 2.f, 10.f});
    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape block({25.f, 15.f});
        block.setFillColor(sf::Color::Red);
        block.setPosition({Constants::WINDOW_WIDTH - 120.f + (i * 35.f), 15.f});
        lifeBlocks.push_back(block);
    }
    setupNewWave();
    setupShelters();
}

void PlayingState::setupNewWave() {
    waveNumber++;
    currentAlienSpeed = Constants::ALIEN_SPEED + (10.0f * (waveNumber - 1));
    aliens.clear();
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            int points = (i < 2) ? 20 : 10;
            TextureID initialTexture = (points == 20) ? TextureID::InvaderL1 : TextureID::InvaderM1;
            aliens.emplace_back(gameRef.getTextureManager().get(initialTexture), 100.0f + j * 60.0f, 50.0f + i * 40.0f, points);
        }
    }
}

void PlayingState::setupShelters() {
    shelters.clear();
    // KORREKTUR: Platziert die Shelter symmetrisch über den Bildschirm.
    float y_position = 450.f; // Die Y-Position bleibt gleich.
    float quarter_width = Constants::WINDOW_WIDTH / 4.f;

    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 1, y_position);      // Bei 25% der Bildschirmbreite
    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 2, y_position);      // Bei 50% (Mitte)
    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 3, y_position);      // Bei 75%
}

void PlayingState::handleEvents(Game& game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
    }
}


void PlayingState::update(float deltaTime) {
    if (player.getLives() <= 0) {
        gameRef.changeStateToGameOver(score);
        return;
    }
    player.update(deltaTime);

    if (!player.isInvincible()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (playerShootClock.getElapsedTime() >= playerShootCooldown) {
                sf::Vector2f projectilePosition = {
                    player.getPosition().x,
                    player.getPosition().y - player.getBounds().size.y / 2.f
                };
                playerProjectiles.emplace_back(Projectile::Type::Player, &gameRef.getTextureManager(), projectilePosition, sf::Vector2f(0, -1));
                playerShootClock.restart();
            }
        }
    }

    bool allAliensDefeated = true;
    bool changeDirection = false;
    for (auto& alien : aliens) {
        if (alien.isActive) {
            allAliensDefeated = false;
            alien.move(alienDirection * currentAlienSpeed * deltaTime, 0);
            const auto& alienBounds = alien.getBounds();

            if (alienBounds.position.y + alienBounds.size.y >= Constants::WINDOW_HEIGHT) {
                gameRef.changeStateToGameOver(score);
                return;
            }

            if ((alienDirection > 0 && (alienBounds.position.x + alienBounds.size.x) > Constants::WINDOW_WIDTH) ||
                (alienDirection < 0 && alienBounds.position.x < 0)) {
                changeDirection = true;
            }
        }
    }

    if (allAliensDefeated) setupNewWave();
    if (changeDirection) {
        alienDirection *= -1.0f;
        for (auto& alien : aliens) {
            alien.move(0, 20.0f);
        }
    }

    updateAlienAnimation();
    alienShoot();

    for (auto it = playerProjectiles.begin(); it != playerProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getSprite().getPosition().y < 0) it = playerProjectiles.erase(it); else ++it;
    }
    for (auto it = alienProjectiles.begin(); it != alienProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getSprite().getPosition().y > Constants::WINDOW_HEIGHT) it = alienProjectiles.erase(it); else ++it;
    }

    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
        [](const Explosion& e) { return e.isFinished(); }), explosions.end());

    for(auto& explosion : explosions) {
        explosion.update(deltaTime);
    }

    checkCollisions();
    updateHUD();
}

void PlayingState::updateAlienAnimation() {
    if (animationClock.getElapsedTime() >= animationInterval) {
        isFirstFrame = !isFirstFrame;
        for (auto& alien : aliens) {
            if (alien.isActive) {
                TextureID newTextureId;
                if (alien.scoreValue == 20) {
                    newTextureId = isFirstFrame ? TextureID::InvaderL1 : TextureID::InvaderL2;
                } else {
                    newTextureId = isFirstFrame ? TextureID::InvaderM1 : TextureID::InvaderM2;
                }
                alien.getSprite().setTexture(gameRef.getTextureManager().get(newTextureId));
            }
        }
        animationClock.restart();
    }
}

void PlayingState::updateHUD() {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setOrigin({scoreText.getLocalBounds().size.x / 2.f, 0});
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f, 10.f});
    for(size_t i = 0; i < lifeBlocks.size(); ++i) {
        lifeBlocks[i].setFillColor(i < player.getLives() ? sf::Color::Red : sf::Color(100, 100, 100));
    }
}

void PlayingState::alienShoot() {
    if (alienProjectiles.empty() && alienShootClock.getElapsedTime() >= alienShootInterval) {
        std::vector<int> activeAlienIndices;
        for (size_t i = 0; i < aliens.size(); ++i) {
            if (aliens[i].isActive) activeAlienIndices.push_back(i);
        }
        if (!activeAlienIndices.empty()) {
            int randomIndex = activeAlienIndices[rand() % activeAlienIndices.size()];
            alienProjectiles.emplace_back(Projectile::Type::Alien, &gameRef.getTextureManager(), aliens[randomIndex].getPosition(), sf::Vector2f(0, 1));
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
                    score += alien.scoreValue;
                    explosions.emplace_back(gameRef.getTextureManager().get(TextureID::InvaderExplosion), alien.getPosition());
                    return true;
                }
            }
            for (auto& shelter : shelters) {
                if (projectile.isActive && !shelter.isDestroyed() && projectile.getBounds().findIntersection(shelter.getBounds())) {
                    projectile.isActive = false;
                    shelter.takeDamage();
                    return true;
                }
            }
            return false;
        }), playerProjectiles.end());

    alienProjectiles.erase(std::remove_if(alienProjectiles.begin(), alienProjectiles.end(),
        [this](Projectile& projectile) {
            if (projectile.isActive && !player.isInvincible() && projectile.getBounds().findIntersection(player.getBounds())) {
                player.handleHit();
                explosions.emplace_back(gameRef.getTextureManager().get(TextureID::PlayerExplosion), player.getPosition(), 3.0f);
                if (player.getLives() > 0) player.respawn();
                return true;
            }
            for (auto& shelter : shelters) {
                if (projectile.isActive && !shelter.isDestroyed() && projectile.getBounds().findIntersection(shelter.getBounds())) {
                    projectile.isActive = false;
                    shelter.takeDamage();
                    return true;
                }
            }
            return false;
        }), alienProjectiles.end());
}

void PlayingState::draw(sf::RenderWindow& window) {
    if (player.getLives() > 0) {
        window.draw(player.getSprite());
    }
    for (const auto& alien : aliens) {
        if(alien.isActive) window.draw(alien.getSprite());
    }
    for (const auto& projectile : playerProjectiles) {
        if(projectile.isActive) window.draw(projectile.getSprite());
    }
    for (const auto& projectile : alienProjectiles) {
        if(projectile.isActive) window.draw(projectile.getSprite());
    }
    for (auto& explosion : explosions) {
        explosion.draw(window);
    }
    for (auto& shelter : shelters) {
        shelter.draw(window);
    }
    window.draw(scoreText);
    for(const auto& block : lifeBlocks) {
        window.draw(block);
    }
}