#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include "../src/model/Player.hpp"
#include "../src/model/Constants.hpp"

// Für diese Logiktests brauchen wir keine echte Textur.
// Eine default-konstruierte sf::Texture reicht
static sf::Texture makeDummyTexture() {
    return sf::Texture{};
}

TEST(PlayerTest, StartsAtCenterBottom) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    const auto pos = player.getPosition();
    const float expectedX = Constants::WINDOW_WIDTH / 2.0f;
    const float expectedY = Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET;

    EXPECT_NEAR(pos.x, expectedX, 0.001f);
    EXPECT_NEAR(pos.y, expectedY, 0.001f);

    // Keine Annahme über Bounds > 0, da Textur leer sein kann.
}

TEST(PlayerTest, MoveLeftMovesAndClampsAtLeftEdge) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    const float dt = 0.5f;

    // Erst nach rechts bewegen, damit eine echte Linksbewegung messbar ist
    player.moveRight(dt);
    const float xAfterRight = player.getPosition().x;

    player.moveLeft(dt);
    EXPECT_LT(player.getPosition().x, xAfterRight);

    // Viele Schritte nach links: darf nicht über den linken Rand hinaus
    for (int i = 0; i < 1000; ++i) {
        player.moveLeft(dt);
    }

    // Bei leerer Textur ist halfWidth = 0; dann muss x >= 0 gelten.
    const auto bounds = player.getBounds();
    const float halfWidth = bounds.size.x / 2.0f;
    EXPECT_GE(player.getPosition().x, halfWidth - 1e-4f);
}

TEST(PlayerTest, MoveRightMovesAndClampsAtRightEdge) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    const float dt = 0.5f;

    // Viele Schritte nach rechts
    for (int i = 0; i < 1000; ++i) {
        player.moveRight(dt);
    }
    const auto bounds = player.getBounds();
    const float halfWidth = bounds.size.x / 2.0f;
    const float rightLimit = Constants::WINDOW_WIDTH - halfWidth;

    EXPECT_LE(player.getPosition().x, rightLimit + 1e-4f);
}

TEST(PlayerTest, HandleHitReducesLivesAndSetsInvincibility) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    const int livesBefore = player.getLives();
    player.handleHit();

    EXPECT_EQ(player.getLives(), livesBefore - 1);
    EXPECT_TRUE(player.isInvincible());

    // Während Invincibility sollen weitere Treffer keine Leben abziehen
    player.handleHit();
    EXPECT_EQ(player.getLives(), livesBefore - 1);
}

TEST(PlayerTest, RespawnCentersAndIsInvincibleImmediately) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    player.moveRight(1.0f);
    player.moveRight(1.0f);

    player.respawn();

    const auto pos = player.getPosition();
    EXPECT_NEAR(pos.x, Constants::WINDOW_WIDTH / 2.0f, 0.001f);
    EXPECT_NEAR(pos.y, Constants::WINDOW_HEIGHT - Constants::PLAYER_START_Y_OFFSET, 0.001f);

    EXPECT_TRUE(player.isInvincible());
}

TEST(PlayerTest, InvincibilityWearsOffAfterDuration) {
    sf::Texture tex = makeDummyTexture();
    Player player(tex);

    player.handleHit();
    EXPECT_TRUE(player.isInvincible());

    // Direkt danach sollte Invincibility noch aktiv sein
    player.update(0.0f);
    EXPECT_TRUE(player.isInvincible());

    // Simuliere Ablauf der Invincibility-Dauer
    sf::sleep(sf::seconds(Constants::PLAYER_INVINCIBILITY_DURATION) + sf::milliseconds(10));

    player.update(0.0f);
    EXPECT_FALSE(player.isInvincible());
}
