#include "Starfield.hpp"
#include "../model/Constants.hpp"
#include <random>

Starfield::Starfield() : numStars(200) {
    stars.resize(numStars);
    srand(time(NULL));

    for (int i = 0; i < numStars; ++i) {
        float x = static_cast<float>(rand() % Constants::WINDOW_WIDTH);
        float y = static_cast<float>(rand() % Constants::WINDOW_HEIGHT);
        float size = (rand() % 2 == 0) ? 1.0f : 2.0f;

        stars[i].shape.setSize({size, size});
        stars[i].shape.setPosition({x, y});
        stars[i].shape.setFillColor(sf::Color::White);

        stars[i].speed = static_cast<float>(rand() % 50 + 20);

        stars[i].twinkleDuration = sf::seconds(static_cast<float>(rand() % 5 + 1));
        stars[i].twinkleClock.restart();
    }
}

void Starfield::update(float deltaTime) {
    for (auto& star : stars) {
        star.shape.move({0.f, star.speed * deltaTime});

        if (star.shape.getPosition().y > Constants::WINDOW_HEIGHT) {
            star.shape.setPosition({static_cast<float>(rand() % Constants::WINDOW_WIDTH), 0.f});
        }

        if (star.twinkleClock.getElapsedTime() > star.twinkleDuration) {
            int alpha = rand() % 156 + 100;
            star.shape.setFillColor(sf::Color(255, 255, 255, alpha));

            star.twinkleDuration = sf::seconds(static_cast<float>(rand() % 5 + 1));
            star.twinkleClock.restart();
        }
    }
}

void Starfield::draw(sf::RenderWindow& window) {
    for (const auto& star : stars) {
        window.draw(star.shape);
    }
}
