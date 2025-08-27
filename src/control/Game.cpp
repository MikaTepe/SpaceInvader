#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game() : alienDirection(Constants::ALIEN_SPEED, 0.f) {
    spawnAliens();
    srand(time(nullptr));
}

void Game::spawnAliens() {
    aliens.clear();
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            aliens.emplace_back(j * 60.f + 50.f, i * 50.f + 50.f);
        }
    }
}

void Game::run() {
    while (view.getWindow().isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (view.getWindow().pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                view.getWindow().close();
                break;
            default:
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    if (key == sf::Keyboard::Right)
        isMovingRight = isPressed;
    if (key == sf::Keyboard::Space && isPressed) {
        if (shootClock.getElapsedTime().asSeconds() > 0.5f) {
            projectiles.emplace_back(player.getPosition().x + 22.f, player.getPosition().y, Projectile::PlayerShot);
            shootClock.restart();
        }
    }
}

void Game::update() {
    if (isMovingLeft) player.moveLeft();
    if (isMovingRight) player.moveRight();

    // Alien Bewegung
    bool changeDirection = false;
    for (const auto& alien : aliens) {
        if (!alien.isActive) continue;
        if ((alien.getPosition().x <= 0 && alienDirection.x < 0) || (alien.getPosition().x >= Constants::WINDOW_WIDTH - 40 && alienDirection.x > 0)) {
            changeDirection = true;
            break;
        }
    }

    if (changeDirection) {
        alienDirection.x *= -1;
        for (auto& alien : aliens) {
            alien.move(0, 40.f);
        }
    } else {
        for (auto& alien : aliens) {
            alien.move(alienDirection.x, 0);
        }
    }

    // Geschosse bewegen und Kollisionen prüfen
    for (auto& projectile : projectiles) {
        projectile.move();
        if (projectile.type == Projectile::PlayerShot) {
            for (auto& alien : aliens) {
                if (alien.isActive && projectile.getBounds().intersects(alien.getBounds())) {
                    alien.isActive = false;
                    projectile.isActive = false;
                    if (rand() % 10 == 0) {
                        powerUps.emplace_back(alien.getPosition().x, alien.getPosition().y, PowerUp::ExtraLife);
                    }
                    break;
                }
            }
        }
    }

    // Power-Ups bewegen und Kollisionen prüfen
    for (auto& powerUp : powerUps) {
        powerUp.move();
        if (powerUp.getBounds().intersects(player.getBounds())) {
            if (powerUp.type == PowerUp::ExtraLife) {
                player.lives++;
            }
            powerUp.isActive = false;
        }
    }

    // Inaktive Objekte entfernen
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) { return !p.isActive || p.getPosition().y < 0 || p.getPosition().y > Constants::WINDOW_HEIGHT; }), projectiles.end());
    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), [](const PowerUp& p) { return !p.isActive; }), powerUps.end());
}

void Game::render() {
    view.draw(player, aliens, projectiles, powerUps);
}