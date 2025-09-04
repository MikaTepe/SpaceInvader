#include "PlayingState.hpp"
#include "Game.hpp"
#include "../model/Constants.hpp"
#include "../view/TextureManager.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <algorithm>

// -----------------------------------------------------------------------------
// PlayingState
//
// Dies ist der "laufende" Spielzustand – hier passiert das eigentliche Space-Invaders-
// Geschehen: Spieler bewegen, Aliens marschieren, Projektile fliegen, Punkte zählen.
// Die Kommentare sind absichtlich menschlich gehalten: kurz, hilfreich, ohne Roman.
// -----------------------------------------------------------------------------

PlayingState::PlayingState(Game& game)
    : gameRef(game),
      player(game.getTextureManager().get(TextureID::Player)),
      alienDirection(Constants::ALIEN_DIRECTION_RIGHT),
      score(0),
      waveNumber(0),
      playerShootCooldown(sf::seconds(Constants::PLAYER_SHOOT_COOLDOWN)),
      alienShootInterval(sf::seconds(Constants::ALIEN_SHOOT_INTERVAL)),
      animationInterval(sf::seconds(Constants::ALIEN_ANIMATION_INTERVAL)),
      isFirstFrame(true),
      scoreText(game.getFont(), "Score: 0", Constants::HUD_FONT_SIZE),
      randomEngine(std::random_device{}())
{
    // Score in weiß und mittig oben platzieren
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f - scoreText.getLocalBounds().size.x / 2.f, Constants::SCORE_TEXT_Y});

    // Leben als kleine rote Blöcke rechts oben anzeigen
    for (int i = 0; i < Constants::PLAYER_INITIAL_LIVES; ++i) {
        sf::RectangleShape block({Constants::LIFE_BLOCK_WIDTH, Constants::LIFE_BLOCK_HEIGHT});
        block.setFillColor(sf::Color::Red);
        block.setPosition({Constants::WINDOW_WIDTH - Constants::LIFE_BLOCK_START_X_OFFSET + (i * Constants::LIFE_BLOCK_SPACING), Constants::LIFE_BLOCK_Y});
        lifeBlocks.push_back(block);
    }

    // Startaufstellung: Aliens & Schutzbunker
    setupNewWave();
    setupShelters();
}

// Neue Welle vorbereiten: Aliens resetten, Tempo leicht erhöhen, Punkte je Reihe setzen
void PlayingState::setupNewWave() {
    waveNumber++;

    // Mit jeder Welle werden die Aliens ein schneller, damit es schwieriger wird.
    currentAlienSpeed = Constants::ALIEN_SPEED + (Constants::ALIEN_SPEED_INCREASE_PER_WAVE * (waveNumber - 1));

    aliens.clear();

    // Aliens in einem Gitter platzieren
    for (int i = 0; i < Constants::ALIEN_ROWS; ++i) {
        for (int j = 0; j < Constants::ALIEN_COLS; ++j) {
            // Obere Reihen bringen mehr Punkte
            int points = (i < 2) ? Constants::ALIEN_TOP_ROW_SCORE : Constants::ALIEN_BOTTOM_ROW_SCORE;

            // Textur je nach Reihe
            TextureID initialTexture = (points == Constants::ALIEN_TOP_ROW_SCORE) ? TextureID::InvaderL1 : TextureID::InvaderM1;

            aliens.emplace_back(
                gameRef.getTextureManager().get(initialTexture),
                Constants::ALIEN_START_X + j * Constants::ALIEN_SPACING_X,
                Constants::ALIEN_START_Y + i * Constants::ALIEN_SPACING_Y,
                points
            );
        }
    }
}

// Schutzbunker spawnen – drei Stück, gleichmäßig verteilt
void PlayingState::setupShelters() {
    shelters.clear();
    float y_position = Constants::SHELTER_Y_POSITION;
    float quarter_width = Constants::WINDOW_WIDTH / 4.f;

    // Bunker einspawnen
    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 1, y_position);
    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 2, y_position);
    shelters.emplace_back(gameRef.getTextureManager(), quarter_width * 3, y_position);
}

// Event-Schleife: Fenster schließen & Co.
void PlayingState::handleEvents(Game& game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
    }
}

// Der große Update-Tick – wird einmal pro Frame aufgerufen
void PlayingState::update(float deltaTime) {
    // Game Over? Dann GameState ändern
    if (player.getLives() <= 0) {
        gameRef.changeStateToGameOver(score);
        return;
    }

    // Erst Eingaben verarbeiten, dann alles andere bewegen/prüfen
    handleInput(deltaTime);
    player.update(deltaTime);

    updateAliens(deltaTime);
    updateProjectiles(deltaTime);
    updateExplosions(deltaTime);

    checkCollisions();
    updateHUD();
}

// Links/Rechts bewegen und schießen
void PlayingState::handleInput(float deltaTime) {
    // Kurz unverwundbar, dann keinen input
    if (player.isInvincible()) return;

    // Pfeiltasten oder WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player.moveLeft(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player.moveRight(deltaTime);
    }

    // Space zum Feuern
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (playerShootClock.getElapsedTime() >= playerShootCooldown) {
            sf::Vector2f projectilePosition = {
                player.getPosition().x,              // aus der Mitte des Schiffs
                player.getBounds().position.y        // knapp oberhalb des Spielers
            };

            // Projektil nach oben
            playerProjectiles.emplace_back(
                Projectile::Type::Player,
                &gameRef.getTextureManager(),
                projectilePosition,
                sf::Vector2f(0, -1)
            );
            playerShootClock.restart();
        }
    }
}

void PlayingState::updateAliens(float deltaTime) {
    bool allAliensDefeated = true;   // Optimistenmodus: alle weg, bis das Gegenteil bewiesen ist
    bool changeDirection = false;    // Müssen wir am Rand umdrehen?

    for (auto& alien : aliens) {
        if (alien.isActive) {
            allAliensDefeated = false;

            alien.move(alienDirection * currentAlienSpeed * deltaTime, 0);
            const auto& alienBounds = alien.getBounds();

            // Wenn die Aliens unten ankommen -> Game Over
            if (alienBounds.position.y + alienBounds.size.y >= Constants::WINDOW_HEIGHT) {
                gameRef.changeStateToGameOver(score);
                return;
            }

            // Rand getroffen
            if ((alienDirection > 0 && (alienBounds.position.x + alienBounds.size.x) > Constants::WINDOW_WIDTH) ||
                (alienDirection < 0 && alienBounds.position.x < 0)) {
                changeDirection = true;
            }
        }
    }

    // Nächste Welle wenn alle tot
    if (allAliensDefeated) {
        setupNewWave();
    }

    if (changeDirection) {
        alienDirection *= -1.0f;
        for (auto& alien : aliens) {
            alien.move(0, Constants::ALIEN_MOVE_DOWN_STEP);
        }
    }

    // Kleine Zweiframe-Animation
    updateAlienAnimation();

    alienShoot();
}

// ----------------------------- Projektile ------------------------------------
void PlayingState::updateProjectiles(float deltaTime) {
    // Spielerprojektile: nach oben, außerhalb des Fensters wegwerfen
    for (auto it = playerProjectiles.begin(); it != playerProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getSprite().getPosition().y < 0) {
            it = playerProjectiles.erase(it);
        } else {
            ++it;
        }
    }

    // Alienprojektile: nach unten, außerhalb des Fensters wegwerfen
    for (auto it = alienProjectiles.begin(); it != alienProjectiles.end(); ) {
        it->update(deltaTime);
        if (it->getSprite().getPosition().y > Constants::WINDOW_HEIGHT) {
            it = alienProjectiles.erase(it);
        } else {
            ++it;
        }
    }
}

// Kurze Lebensdauer
void PlayingState::updateExplosions(float deltaTime) {
    // Erst alle fertigen Explosionen entsorgen
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
        [](const Explosion& e) { return e.isFinished(); }), explosions.end());

    // Die übrigen weiter ticken lassen
    for(auto& explosion : explosions) {
        explosion.update(deltaTime);
    }
}

// Zwei-Frame-Animation der Aliens
void PlayingState::updateAlienAnimation() {
    if (animationClock.getElapsedTime() >= animationInterval) {
        isFirstFrame = !isFirstFrame;
        for (auto& alien : aliens) {
            if (alien.isActive) {
                TextureID newTextureId;
                if (alien.scoreValue == Constants::ALIEN_TOP_ROW_SCORE) {
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

// HUD aktuell halten: Score zentrieren, Lebensblöcke einfärben
void PlayingState::updateHUD() {
    scoreText.setString("Score: " + std::to_string(score));

    // Nach dem Textwechsel die Mitte neu ausrichten
    scoreText.setOrigin({scoreText.getLocalBounds().size.x / 2.f, 0});
    scoreText.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::SCORE_TEXT_Y});

    // Rote Blöcke für verbleibende Leben, graue für verlorene Leben
    for(size_t i = 0; i < lifeBlocks.size(); ++i) {
        lifeBlocks[i].setFillColor(i < static_cast<size_t>(player.getLives()) ? sf::Color::Red : sf::Color(100, 100, 100));
    }
}

// Ein Alien sucht sich zufällig einen Schützen
void PlayingState::alienShoot() {
    // Immer nur schießen, wenn gerade kein Aliengeschoss gespwant wurde
    if (alienProjectiles.empty() && alienShootClock.getElapsedTime() >= alienShootInterval) {
        std::vector<int> activeAlienIndices;
        for (size_t i = 0; i < aliens.size(); ++i) {
            if (aliens[i].isActive) {
                activeAlienIndices.push_back(static_cast<int>(i));
            }
        }
        if (!activeAlienIndices.empty()) {
            // Zufallszahlengenerierung
            alienDistribution.param(std::uniform_int_distribution<size_t>::param_type(0, activeAlienIndices.size() - 1));
            int randomIndex = activeAlienIndices[alienDistribution(randomEngine)];

            // Projektil vom ausgewählten Alien straight nach unten
            alienProjectiles.emplace_back(
                Projectile::Type::Alien,
                &gameRef.getTextureManager(),
                aliens[static_cast<size_t>(randomIndex)].getPosition(),
                sf::Vector2f(0, 1)
            );
            alienShootClock.restart();
        }
    }
}

// Hilfsfunktion: checkt, ob ein Projektil einen Bunker trifft und wendet Schaden an
bool PlayingState::checkProjectileShelterCollision(Projectile& projectile) {
    for (auto& shelter : shelters) {
        if (!shelter.isDestroyed() && projectile.getBounds().findIntersection(shelter.getBounds())) {
            shelter.takeDamage();
            return true; // Projektil verbraucht
        }
    }
    return false;
}

// ------------------------------ Kollisionen ----------------------------------
void PlayingState::checkCollisions() {
    // Kollisionen der Spieler-Projektile
    playerProjectiles.erase(std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
        [this](Projectile& projectile) {
            if (!projectile.isActive) return false;

            // Bunker zuerst
            if (checkProjectileShelterCollision(projectile)) {
                projectile.isActive = false;
                return true; // aus Liste entfernen
            }

            //Treffer gibt Punkte und eine kleine Explosion
            for (auto& alien : aliens) {
                if (alien.isActive && projectile.getBounds().findIntersection(alien.getBounds())) {
                    projectile.isActive = false;
                    alien.isActive = false;
                    score += alien.scoreValue;
                    explosions.emplace_back(
                        gameRef.getTextureManager().get(TextureID::InvaderExplosion),
                        alien.getPosition()
                    );
                    return true; // Projektil kann weg
                }
            }
            return false; // nix getroffen -> bleibt erst mal
        }), playerProjectiles.end());

    // Kollisionen der Alien-Projektile
    alienProjectiles.erase(std::remove_if(alienProjectiles.begin(), alienProjectiles.end(),
        [this](Projectile& projectile) {
            if (!projectile.isActive) return false;

            // Bunker fangen projektile ab
            if (checkProjectileShelterCollision(projectile)) {
                projectile.isActive = false;
                return true;
            }

            // Spieler getroffen, dann Leben verlieren + Respawn mit Invinciblity
            if (!player.isInvincible() && projectile.getBounds().findIntersection(player.getBounds())) {
                player.handleHit();
                explosions.emplace_back(
                    gameRef.getTextureManager().get(TextureID::PlayerExplosion),
                    player.getPosition(),
                    Constants::PLAYER_EXPLOSION_SCALE
                );
                if (player.getLives() > 0) player.respawn();
                return true;
            }
            return false;
        }), alienProjectiles.end());
}

void PlayingState::draw(sf::RenderWindow& window) {
    // Den Spieler nur anzeigen, wenn er überhaupt noch da ist
    if (player.getLives() > 0) {
        window.draw(player.getSprite());
    }

    // Aktive Aliens zeigen
    for (const auto& alien : aliens) {
        if(alien.isActive) window.draw(alien.getSprite());
    }

    // Projektile
    for (const auto& projectile : playerProjectiles) {
        if(projectile.isActive) window.draw(projectile.getSprite());
    }
    for (const auto& projectile : alienProjectiles) {
        if(projectile.isActive) window.draw(projectile.getSprite());
    }

    // Explosion
    for (auto& explosion : explosions) {
        explosion.draw(window);
    }

    // Bunker zuletzt vor HUD
    for (auto& shelter : shelters) {
        shelter.draw(window);
    }

    // HUD (Score & Leben)
    window.draw(scoreText);
    for(const auto& block : lifeBlocks) {
        window.draw(block);
    }
}
