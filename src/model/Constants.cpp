#include "Constants.hpp"

namespace Constants {
    // Window Settings
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int FRAME_RATE_LIMIT = 60;
    const char* FONT_PATH = "assets/fonts/DejaVuSansMono.ttf";

    // Game Settings
    const char* HIGHSCORE_FILE = "highscore.txt";

    // Gameplay Values
    const float PLAYER_SPEED = 200.0f;
    const float ALIEN_SPEED = 30.0f;
    const float PROJECTILE_SPEED = 200.0f;
    const float POWERUP_SPEED = 150.0f;
    const float PLAYER_SHOOT_COOLDOWN = 0.4f;
    const float ALIEN_SHOOT_INTERVAL = 1.0f;
    const float ALIEN_ANIMATION_INTERVAL = 1.0f;
    const float ALIEN_SPEED_INCREASE_PER_WAVE = 10.0f;
    const float ALIEN_MOVE_DOWN_STEP = 20.0f;

    // Player
    const int PLAYER_INITIAL_LIVES = 3;
    const float PLAYER_SCALE = 2.0f;
    const float PLAYER_START_Y_OFFSET = 50.f;
    const float PLAYER_INVINCIBILITY_DURATION = 2.0f;
    const sf::Color PLAYER_HIT_COLOR = sf::Color(128, 128, 128, 180);

    // Alien
    const int ALIEN_ROWS = 5;
    const int ALIEN_COLS = 11;
    const int ALIEN_TOP_ROW_SCORE = 20;
    const int ALIEN_BOTTOM_ROW_SCORE = 10;
    const float ALIEN_START_X = 100.0f;
    const float ALIEN_START_Y = 50.0f;
    const float ALIEN_SPACING_X = 60.0f;
    const float ALIEN_SPACING_Y = 40.0f;
    const float ALIEN_SCALE = 1.5f;

    // Projectile
    const float PROJECTILE_SCALE = 2.0f;
    const float PROJECTILE_ANIMATION_INTERVAL = 0.1f;

    // Shelter
    const float SHELTER_Y_POSITION = 450.f;
    const int SHELTER_INITIAL_HEALTH = 30;
    const float SHELTER_SCALE = 2.0f;
    const int SHELTER_HEALTH_FONT_SIZE = 12;
    const int SHELTER_DAMAGE_LEVELS = 9;
    const int SHELTER_HEALTH_PER_DAMAGE_LEVEL = 3;
    const float SHELTER_HEALTH_TEXT_Y_OFFSET = 15.f;


    // HUD
    const int HUD_FONT_SIZE = 24;
    const float SCORE_TEXT_Y = 10.f;
    const float LIFE_BLOCK_WIDTH = 25.f;
    const float LIFE_BLOCK_HEIGHT = 15.f;
    const float LIFE_BLOCK_Y = 15.f;
    const float LIFE_BLOCK_SPACING = 35.f;
    const float LIFE_BLOCK_START_X_OFFSET = 120.f;

    // Start Screen
    const int TITLE_FONT_SIZE = 60;
    const int INSTRUCTION_FONT_SIZE_START = 30;
    const int HIGHSCORE_FONT_SIZE_START = 24;
    const float TITLE_Y_OFFSET = -100.f;
    const float HIGHSCORE_Y_OFFSET = 50.f;

    // Game Over Screen
    const int GAME_OVER_FONT_SIZE = 70;
    const int SCORE_FONT_SIZE = 30;
    const int INSTRUCTION_FONT_SIZE = 24;
    const float GAME_OVER_Y_OFFSET = -150.f;
    const float SCORE_Y_OFFSET = -50.f;
    const float INSTRUCTION_Y_OFFSET = 100.f;
    const sf::Color INSTRUCTION_COLOR = sf::Color(180, 180, 180);

    // Effects
    const float EXPLOSION_DURATION = 0.5f;
    const float PLAYER_EXPLOSION_SCALE = 3.0f;
    const int STARFIELD_NUM_STARS = 200;
    const float STAR_SIZE_SMALL = 1.0f;
    const float STAR_SIZE_LARGE = 2.0f;
    const int STAR_SPEED_MIN = 20;
    const int STAR_SPEED_MAX = 50;
    const int STAR_TWINKLE_DURATION_MIN = 1;
    const int STAR_TWINKLE_DURATION_MAX = 5;
    const int STAR_ALPHA_MIN = 100;
    const int STAR_ALPHA_MAX = 255;
}
