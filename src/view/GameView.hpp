#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../model/Player.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include "../model/PowerUp.hpp"
#include "Layer.hpp"

class GameView {
public:
    GameView();
    void draw(const Player& player, const std::vector<Alien>& aliens, const std::vector<Projectile>& projectiles, const std::vector<PowerUp>& powerUps);
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow window;
    // Hier könntest du Layer für Hintergründe etc. hinzufügen
};

#endif //GAMEVIEW_HPP