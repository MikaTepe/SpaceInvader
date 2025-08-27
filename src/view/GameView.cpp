#include "GameView.hpp"
#include "../model/Constants.hpp"

GameView::GameView() : window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Space Invaders") {
    window.setFramerateLimit(60);
}

sf::RenderWindow& GameView::getWindow() {
    return window;
}

void GameView::draw(const Player& player, const std::vector<Alien>& aliens, const std::vector<Projectile>& projectiles, const std::vector<PowerUp>& powerUps) {
    window.clear();

    // Zeichne Spieler
    window.draw(player.getShape());

    // Zeichne Aliens
    for (const auto& alien : aliens) {
        if(alien.isActive) window.draw(alien.getShape());
    }

    // Zeichne Geschosse
    for (const auto& projectile : projectiles) {
        if(projectile.isActive) window.draw(projectile.getShape());
    }

    // Zeichne Power-Ups
    for (const auto& powerUp : powerUps) {
        if(powerUp.isActive) window.draw(powerUp.getShape());
    }

    window.display();
}