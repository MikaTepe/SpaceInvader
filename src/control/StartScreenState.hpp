#ifndef STARTSCREENSTATE_HPP
#define STARTSCREENSTATE_HPP

#include "GameState.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class StartScreenState : public GameState {
public:
    explicit StartScreenState(Game& game);

    void handleEvents(Game& game) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text titleText;
    sf::Text instructionText;
    sf::Text highScoreText;
};

#endif //STARTSCREENSTATE_HPP
