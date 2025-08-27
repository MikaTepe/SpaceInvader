#include "gtest/gtest.h"
#include "../src/model/Player.hpp"

TEST(PlayerTest, MoveLeft) {
    Player player;
    float initialX = player.getPosition().x;

    // Test 1: Normale Bewegung nach links
    player.moveLeft();
    ASSERT_LT(player.getPosition().x, initialX);

    // Test 2: Bewegung stoppt am linken Rand
    player.shape.setPosition(0, player.getPosition().y);
    player.moveLeft();
    ASSERT_EQ(player.getPosition().x, 0);

    // Test 3: Mehrfache Bewegung nach links
    player.shape.setPosition(100, 100);
    player.moveLeft();
    player.moveLeft();
    ASSERT_FLOAT_EQ(player.getPosition().x, 100 - 2 * 5.0f);
}