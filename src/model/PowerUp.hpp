#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "GameObject.hpp"
#include "Constants.hpp"
#include <SFML/Graphics/Texture.hpp>

class PowerUp : public GameObject {
public:
    PowerUp(const sf::Texture& texture, float startX, float startY);

    void update(float deltaTime) override;
};

#endif //POWERUP_HPP