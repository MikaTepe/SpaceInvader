#include "Starfield.hpp"
#include "../model/Constants.hpp"
#include <random>

Starfield::Starfield() : numStars(Constants::STARFIELD_NUM_STARS) {
    stars.resize(numStars);
    srand(time(NULL));

    for (int i = 0; i < numStars; ++i) {
        float x = static_cast<float>(rand() % Constants::WINDOW_WIDTH);
        float y = static_cast<float>(rand() % Constants::WINDOW_HEIGHT);
        float size = (rand() % 2 == 0) ? Constants::STAR_SIZE_SMALL : Constants::STAR_SIZE_LARGE;

        stars[i].shape.setSize({size, size});
        stars[i].shape.setPosition({x, y});
        stars[i].shape.setFillColor(sf::Color::White);

        stars[i].speed = static_cast<float>(rand() % (Constants::STAR_SPEED_MAX - Constants::STAR_SPEED_MIN + 1) + Constants::STAR_SPEED_MIN);

        stars[i].twinkleDuration = sf::seconds(static_cast<float>(rand() % (Constants::STAR_TWINKLE_DURATION_MAX - Constants::STAR_TWINKLE_DURATION_MIN + 1) + Constants::STAR_TWINKLE_DURATION_MIN));
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
            int alpha = rand() % (Constants::STAR_ALPHA_MAX - Constants::STAR_ALPHA_MIN + 1) + Constants::STAR_ALPHA_MIN;
            star.shape.setFillColor(sf::Color(255, 255, 255, alpha));

            star.twinkleDuration = sf::seconds(static_cast<float>(rand() % (Constants::STAR_TWINKLE_DURATION_MAX - Constants::STAR_TWINKLE_DURATION_MIN + 1) + Constants::STAR_TWINKLE_DURATION_MIN));
            star.twinkleClock.restart();
        }
    }
}

void Starfield::draw(sf::RenderWindow& window) {
    for (const auto& star : stars) {
        window.draw(star.shape);
    }
}