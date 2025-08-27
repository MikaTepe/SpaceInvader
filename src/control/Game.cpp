#include "Game.hpp"
#include "../model/Constants.hpp"

Game::Game() : player(), alienDirection(1.0f) {
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
    for (auto event = view.getWindow().pollEvent(); event; event = view.getWindow().pollEvent())
    {
        // Wir prüfen den Typ des Events mit der 'is'-Methode
        if (event->is<sf::Event::Closed>()) {
            view.getWindow().close();
        }
        // Wenn das Event ein 'KeyPressed' ist, holen wir uns die Daten dazu
        else if (const auto* keyPressed = event->get<sf::Event::KeyPressed>()) {
            handlePlayerInput(keyPressed->code, true);
        }
        // Wenn das Event ein 'KeyReleased' ist, holen wir uns die Daten dazu
        else if (const auto* keyReleased = event->get<sf::Event::KeyReleased>()) {
            handlePlayerInput(keyReleased->code, false);
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    // Tastencodes sind jetzt in einem Key-Enum
    if (key == sf::Keyboard::Key::Left) {
        player.isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Key::Right) {
        player.isMovingRight = isPressed;
    } else if (key == sf::Keyboard::Key::Space && isPressed) {
        const auto& playerShape = player.getShape();
        projectiles.emplace_back(playerShape.getPosition().x, playerShape.getPosition().y, 0.f, -1.f);
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);

    bool changeDirection = false;
    for (auto& alien : aliens) {
        if (alien.isActive) {
            alien.move(alienDirection * Constants::ALIEN_SPEED * deltaTime, 0);
            const auto& alienShape = alien.getShape();
            if (alienShape.getPosition().x < alienShape.getSize().x / 2.f ||
                alienShape.getPosition().x > Constants::WINDOW_WIDTH - alienShape.getSize().x / 2.f) {
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
            powerUp.applyEffect(player);
        }
    }
}

void Game::render() {
    view.draw(player, aliens, projectiles, powerUps);
}