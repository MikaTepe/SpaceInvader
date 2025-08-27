#include "Game.hpp"
#include "../model/Constants.hpp"
#include "../view/GameView.hpp"
#include <SFML/Window/Event.hpp>

Game::Game() : view(), player(), alienDirection(1.0f) {
    // Initialisiert die Aliens in einem Gitter
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            aliens.emplace_back(100.0f + j * 60.0f, 50.0f + i * 40.0f);
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (view.getWindow().isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    // Korrekte Event-Schleife für SFML 3. 'pollEvent' gibt ein std::optional zurück.
    while (auto event = view.getWindow().pollEvent())
    {
        // Wir prüfen den Typ des Events mit der 'is'-Methode.
        if (event->is<sf::Event::Closed>()) {
            view.getWindow().close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            handlePlayerInput(keyPressed->code, true);
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            handlePlayerInput(keyReleased->code, false);
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Key::Left) {
        player.isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Key::Right) {
        player.isMovingRight = isPressed;
    } else if (key == sf::Keyboard::Key::Space && isPressed) {
        const auto& playerShape = player.getShape();
        projectiles.emplace_back(playerShape.getPosition().x, playerShape.getPosition().y, 0.f, -Constants::PROJECTILE_SPEED);
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);

    bool changeDirection = false;
    for (auto& alien : aliens) {
        if (alien.isActive) {
            alien.move(alienDirection * Constants::ALIEN_SPEED, 0);
            const auto& alienBounds = alien.getBounds();
            if (alienBounds.position.x < 0 || (alienBounds.position.x + alienBounds.size.x) > Constants::WINDOW_WIDTH) {
                changeDirection = true;
            }
        }
    }

    if (changeDirection) {
        alienDirection *= -1.0f;
        for (auto& alien : aliens) {
            alien.move(0, 20.0f);
        }
    }

    for (auto& projectile : projectiles) {
        projectile.update(deltaTime);
    }

    for(auto& powerUp : powerUps){
        powerUp.update(deltaTime);
    }

    checkCollisions();
}

void Game::checkCollisions() {
    for (auto& projectile : projectiles) {
        for (auto& alien : aliens) {
            if (projectile.isActive && alien.isActive && projectile.getBounds().findIntersection(alien.getBounds())) {
                projectile.isActive = false;
                alien.isActive = false;
            }
        }
    }

    for (auto& powerUp : powerUps) {
        if (powerUp.isActive && powerUp.getBounds().findIntersection(player.getBounds())) {
            powerUp.isActive = false;
        }
    }
}

void Game::render() {
    view.draw(player, aliens, projectiles, powerUps);
}