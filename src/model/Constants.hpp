#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics/Color.hpp>

namespace Constants {
    // Window Settings
    extern const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;
    extern const int FRAME_RATE_LIMIT;
    extern const char* FONT_PATH;

    // Game Settings
    extern const char* HIGHSCORE_FILE;

    // Gameplay Values
    extern const float PLAYER_SPEED;
    extern const float ALIEN_SPEED;
    extern const float PROJECTILE_SPEED;
    extern const float POWERUP_SPEED;
    extern const float PLAYER_SHOOT_COOLDOWN;
    extern const float ALIEN_SHOOT_INTERVAL;
    extern const float ALIEN_ANIMATION_INTERVAL;
    extern const float ALIEN_SPEED_INCREASE_PER_WAVE;
    extern const float ALIEN_MOVE_DOWN_STEP;

    // Player
    extern const int PLAYER_INITIAL_LIVES;
    extern const float PLAYER_SCALE;
    extern const float PLAYER_START_Y_OFFSET;
    extern const float PLAYER_INVINCIBILITY_DURATION;
    extern const sf::Color PLAYER_HIT_COLOR;

    // Alien
    extern const int ALIEN_ROWS;
    extern const int ALIEN_COLS;
    extern const int ALIEN_TOP_ROW_SCORE;
    extern const int ALIEN_BOTTOM_ROW_SCORE;
    extern const float ALIEN_START_X;
    extern const float ALIEN_START_Y;
    extern const float ALIEN_SPACING_X;
    extern const float ALIEN_SPACING_Y;
    extern const float ALIEN_SCALE;

    // Projectile
    extern const float PROJECTILE_SCALE;
    extern const float PROJECTILE_ANIMATION_INTERVAL;

    // Shelter
    extern const float SHELTER_Y_POSITION;
    extern const int SHELTER_INITIAL_HEALTH;
    extern const float SHELTER_SCALE;
    extern const int SHELTER_HEALTH_FONT_SIZE;
    extern const int SHELTER_DAMAGE_LEVELS;
    extern const int SHELTER_HEALTH_PER_DAMAGE_LEVEL;
    extern const float SHELTER_HEALTH_TEXT_Y_OFFSET;


    // HUD
    extern const int HUD_FONT_SIZE;
    extern const float SCORE_TEXT_Y;
    extern const float LIFE_BLOCK_WIDTH;
    extern const float LIFE_BLOCK_HEIGHT;
    extern const float LIFE_BLOCK_Y;
    extern const float LIFE_BLOCK_SPACING;
    extern const float LIFE_BLOCK_START_X_OFFSET;

    // Start Screen
    extern const int TITLE_FONT_SIZE;
    extern const int INSTRUCTION_FONT_SIZE_START;
    extern const int HIGHSCORE_FONT_SIZE_START;
    extern const float TITLE_Y_OFFSET;
    extern const float HIGHSCORE_Y_OFFSET;

    // Game Over Screen
    extern const int GAME_OVER_FONT_SIZE;
    extern const int SCORE_FONT_SIZE;
    extern const int INSTRUCTION_FONT_SIZE;
    extern const float GAME_OVER_Y_OFFSET;
    extern const float SCORE_Y_OFFSET;
    extern const float INSTRUCTION_Y_OFFSET;
    extern const sf::Color INSTRUCTION_COLOR;

    // Effects
    extern const float EXPLOSION_DURATION;
    extern const float PLAYER_EXPLOSION_SCALE;
    extern const int STARFIELD_NUM_STARS;
    extern const float STAR_SIZE_SMALL;
    extern const float STAR_SIZE_LARGE;
    extern const int STAR_SPEED_MIN;
    extern const int STAR_SPEED_MAX;
    extern const int STAR_TWINKLE_DURATION_MIN;
    extern const int STAR_TWINKLE_DURATION_MAX;
    extern const int STAR_ALPHA_MIN;
    extern const int STAR_ALPHA_MAX;
}

#endif //CONSTANTS_HPP
