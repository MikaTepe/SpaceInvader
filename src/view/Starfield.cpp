#include "Starfield.hpp"
#include "../model/Constants.hpp"
#include <random>

Starfield::Starfield() : numStars(Constants::STARFIELD_NUM_STARS) {
    stars.resize(numStars);

    // sorgt dafür, dass jeder Start anders aussieht
    srand(time(NULL));

    // Alle Sterne initialisieren: Position, Größe, Geschwindigkeit, Funkel-Intervalle
    for (int i = 0; i < numStars; ++i) {
        // Zufällige Position im Fenster
        float x = static_cast<float>(rand() % Constants::WINDOW_WIDTH);
        float y = static_cast<float>(rand() % Constants::WINDOW_HEIGHT);

        // Zufällige Größe: kleine und große Sterne mischen das Bild auf
        float size = (rand() % 2 == 0)
            ? Constants::STAR_SIZE_SMALL
            : Constants::STAR_SIZE_LARGE;

        // Stern als kleines Quadrat darstellen
        stars[i].shape.setSize({size, size});
        stars[i].shape.setPosition({x, y});
        stars[i].shape.setFillColor(sf::Color::White);

        // Geschwindigkeit zufällig zwischen Minimum und Maximum wählen
        stars[i].speed = static_cast<float>(
            rand() % (Constants::STAR_SPEED_MAX - Constants::STAR_SPEED_MIN + 1)
            + Constants::STAR_SPEED_MIN
        );

        // „Funkel“-Dauer zufällig bestimmen, damit Sterne unterschiedlich blinken
        stars[i].twinkleDuration = sf::seconds(static_cast<float>(
            rand() % (Constants::STAR_TWINKLE_DURATION_MAX - Constants::STAR_TWINKLE_DURATION_MIN + 1)
            + Constants::STAR_TWINKLE_DURATION_MIN
        ));
        stars[i].twinkleClock.restart();
    }
}

// Update pro Frame: Sterne bewegen + Funkel-Effekt aktualisieren
void Starfield::update(float deltaTime) {
    for (auto& star : stars) {
        // Sterne nach unten bewegen
        star.shape.move({0.f, star.speed * deltaTime});

        // Wenn ein Stern unten aus dem Fenster fällt -Y oben wieder einsetzen
        if (star.shape.getPosition().y > Constants::WINDOW_HEIGHT) {
            star.shape.setPosition({
                static_cast<float>(rand() % Constants::WINDOW_WIDTH),
                0.f
            });
        }

        // Funkel-Logik: ab und zu die Transparenz zufällig ändern
        if (star.twinkleClock.getElapsedTime() > star.twinkleDuration) {
            int alpha = rand() % (Constants::STAR_ALPHA_MAX - Constants::STAR_ALPHA_MIN + 1)
                        + Constants::STAR_ALPHA_MIN;

            // Farbe bleibt weiß, nur die Helligkeit ändert sich
            star.shape.setFillColor(sf::Color(255, 255, 255, alpha));

            // Neues Funkel-Intervall setzen und Timer zurücksetzen
            star.twinkleDuration = sf::seconds(static_cast<float>(
                rand() % (Constants::STAR_TWINKLE_DURATION_MAX - Constants::STAR_TWINKLE_DURATION_MIN + 1)
                + Constants::STAR_TWINKLE_DURATION_MIN
            ));
            star.twinkleClock.restart();
        }
    }
}

// Alle Sterne zeichnen
void Starfield::draw(sf::RenderWindow& window) {
    for (const auto& star : stars) {
        window.draw(star.shape);
    }
}