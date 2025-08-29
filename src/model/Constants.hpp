#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <SFML/Graphics/Color.hpp>

namespace Constants {
    // Fenster und Spiel
    inline constexpr int WINDOW_WIDTH = 800;
    inline constexpr int WINDOW_HEIGHT = 600;
    inline constexpr int FRAME_RATE_LIMIT = 60;
    inline const std::string FONT_PATH = "assets/fonts/DejaVuSansMono.ttf";
    inline const std::string HIGHSCORE_FILE = "highscore.txt";

    // Spieler
    inline constexpr float PLAYER_SPEED = 200.0f;
    inline constexpr int PLAYER_INITIAL_LIVES = 3;
    inline constexpr float PLAYER_SCALE = 2.0f;
    inline constexpr float PLAYER_START_Y_OFFSET = 50.0f;
    inline constexpr float PLAYER_INVINCIBILITY_DURATION = 2.0f;
    inline const sf::Color PLAYER_HIT_COLOR = sf::Color(128, 128, 128, 180);
    inline constexpr float PLAYER_SHOOT_COOLDOWN = 0.4f;
    inline constexpr float PLAYER_EXPLOSION_SCALE = 3.0f;

    // Aliens
    inline constexpr int ALIEN_ROWS = 5;
    inline constexpr int ALIEN_COLS = 11;
    inline constexpr float ALIEN_SCALE = 1.5f;
    inline constexpr float ALIEN_SPACING_X = 60.0f;
    inline constexpr float ALIEN_SPACING_Y = 40.0f;
    inline constexpr float ALIEN_START_X = 100.0f;
    inline constexpr float ALIEN_START_Y = 50.0f;
    inline constexpr float ALIEN_SPEED = 30.0f;
    inline constexpr float ALIEN_SPEED_INCREASE_PER_WAVE = 10.0f;
    inline constexpr float ALIEN_MOVE_DOWN_STEP = 20.0f;
    inline constexpr int ALIEN_TOP_ROW_SCORE = 20;
    inline constexpr int ALIEN_BOTTOM_ROW_SCORE = 10;
    inline constexpr float ALIEN_SHOOT_INTERVAL = 1.0f;
    inline constexpr float ALIEN_ANIMATION_INTERVAL = 1.0f;
    inline constexpr float ALIEN_DIRECTION_RIGHT = 1.0f;
    inline constexpr float ALIEN_DIRECTION_LEFT = -1.0f;

    // Projektile
    inline constexpr float PROJECTILE_SPEED = 200.0f;
    inline constexpr float PROJECTILE_SCALE = 2.0f;
    inline constexpr float PROJECTILE_ANIMATION_INTERVAL = 0.1f;

    // PowerUp
    inline constexpr float POWERUP_SPEED = 150.0f;

    // Schutzschilde (Shelter)
    inline constexpr float SHELTER_Y_POSITION = 450.0f;
    inline constexpr int SHELTER_INITIAL_HEALTH = 30;
    inline constexpr float SHELTER_SCALE = 2.0f;
    inline constexpr int SHELTER_HEALTH_FONT_SIZE = 12;
    inline constexpr int SHELTER_DAMAGE_LEVELS = 9;
    inline constexpr int SHELTER_HEALTH_PER_DAMAGE_LEVEL = 3;
    inline constexpr float SHELTER_HEALTH_TEXT_Y_OFFSET = 15.0f;

    // HUD (Heads-Up Display)
    inline constexpr int HUD_FONT_SIZE = 24;
    inline constexpr float SCORE_TEXT_Y = 10.0f;
    inline constexpr float LIFE_BLOCK_WIDTH = 25.0f;
    inline constexpr float LIFE_BLOCK_HEIGHT = 15.0f;
    inline constexpr float LIFE_BLOCK_START_X_OFFSET = 120.0f;
    inline constexpr float LIFE_BLOCK_Y = 15.0f;
    inline constexpr float LIFE_BLOCK_SPACING = 35.0f;

    // Start Screen
    inline constexpr int TITLE_FONT_SIZE = 60;
    inline constexpr int INSTRUCTION_FONT_SIZE_START = 30;
    inline constexpr int HIGHSCORE_FONT_SIZE_START = 24;
    inline constexpr float TITLE_Y_OFFSET = -100.0f;
    inline constexpr float HIGHSCORE_Y_OFFSET = 50.0f;

    // Game Over Screen
    inline constexpr int GAME_OVER_FONT_SIZE = 70;
    inline constexpr int SCORE_FONT_SIZE = 30;
    inline constexpr int INSTRUCTION_FONT_SIZE = 24;
    inline constexpr float GAME_OVER_Y_OFFSET = -150.0f;
    inline constexpr float SCORE_Y_OFFSET = -50.0f;
    inline constexpr float INSTRUCTION_Y_OFFSET = 100.0f;
    inline const sf::Color INSTRUCTION_COLOR = sf::Color(180, 180, 180);

    // Effekte
    inline constexpr float EXPLOSION_DURATION = 0.5f;
    inline constexpr int STARFIELD_NUM_STARS = 200;
    inline constexpr float STAR_SIZE_SMALL = 1.0f;
    inline constexpr float STAR_SIZE_LARGE = 2.0f;
    inline constexpr int STAR_SPEED_MIN = 20;
    inline constexpr int STAR_SPEED_MAX = 50;
    inline constexpr int STAR_TWINKLE_DURATION_MIN = 1;
    inline constexpr int STAR_TWINKLE_DURATION_MAX = 5;
    inline constexpr int STAR_ALPHA_MIN = 100;
    inline constexpr int STAR_ALPHA_MAX = 255;
}

#endif //CONSTANTS_HPP