#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Constants.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

/**
 * @class Player
 * @brief Repräsentiert das Raumschiff des Spielers im Spiel.
 *
 * Diese Klasse verwaltet den Zustand des Spielers, einschließlich Position, Leben und Unverwundbarkeit.
 * Die Logik zur Steuerung (Tastatureingaben) wird hier bewusst herausgehalten und
 * stattdessen im Controller (PlayingState) behandelt, um das MVC-Muster einzuhalten.
 */
class Player : public GameObject {
public:
    /**
     * @brief Konstruktor für ein Spieler-Objekt.
     * @param texture Die Textur für das Sprite des Spielers.
     */
    explicit Player(const sf::Texture& texture);

    /**
     * @brief Aktualisiert den Zustand des Spielers, z.B. den Unverwundbarkeitsstatus.
     * @param deltaTime Die Zeit, die seit dem letzten Frame vergangen ist.
     */
    void update(float deltaTime) override;

    /**
     * @brief Behandelt den Fall, dass der Spieler von einem Projektil getroffen wird.
     * Reduziert die Leben, wenn der Spieler nicht unverwundbar ist.
     */
    void handleHit();

    /**
     * @brief Setzt den Spieler an die Startposition zurück, z.B. nach einem Treffer.
     */
    void respawn();

    /**
     * @brief Bewegt den Spieler nach links, begrenzt durch den Bildschirmrand.
     * @param deltaTime Die Zeit seit dem letzten Frame, um die Bewegung geschwindigkeitsunabhängig zu machen.
     */
    void moveLeft(float deltaTime);

    /**
     * @brief Bewegt den Spieler nach rechts, begrenzt durch den Bildschirmrand.
     * @param deltaTime Die Zeit seit dem letzten Frame, um die Bewegung geschwindigkeitsunabhängig zu machen.
     */
    void moveRight(float deltaTime);

    /**
     * @brief Prüft, ob der Spieler aktuell unverwundbar ist.
     * @return true, wenn der Spieler unverwundbar ist, ansonsten false.
     */
    bool isInvincible() const;

    /**
     * @brief Gibt die aktuelle Anzahl der Leben des Spielers zurück.
     * @return Die Anzahl der verbleibenden Leben.
     */
    int getLives() const;

private:
    float speed;                   ///< Die Bewegungsgeschwindigkeit des Spielers.
    int lives;                     ///< Die Anzahl der verbleibenden Leben.
    bool invincible;               ///< Flag, das anzeigt, ob der Spieler unverwundbar ist.
    sf::Clock invincibilityClock;  ///< Uhr zur Verfolgung der Dauer der Unverwundbarkeit.
    sf::Time invincibilityDuration;///< Die Dauer der Unverwundbarkeit nach einem Treffer.
};

#endif //PLAYER_HPP