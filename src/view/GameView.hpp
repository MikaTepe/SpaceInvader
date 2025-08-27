#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../model/Player.hpp"
#include "../model/Alien.hpp"
#include "../model/Projectile.hpp"
#include "../model/PowerUp.hpp"

class GameView {
public:
    GameView();
    sf::RenderWindow& getWindow();
    void draw(const Player& player, const std::vector<Alien>& aliens, const std::vector<Projectile>& projectiles, const std::vector<PowerUp>& powerUps);

private:
    sf::RenderWindow window;
};

#endif //GAMEVIEW_HPP
