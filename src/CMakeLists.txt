# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Alien.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Projectile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/PowerUp.cpp
    )

# Controller (jetzt mit den neuen State-Klassen)
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/StartScreenState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayingState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/GameOverState.cpp
)

# View (GameView.cpp wurde entfernt, da es nicht mehr benötigt wird)
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
)

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )