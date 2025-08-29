# Model
set(ModelSources
        ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/Alien.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/Projectile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/PowerUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model/Shelter.cpp
)

# Controller
set(ControlSources
        ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/control/StartScreenState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayingState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/control/GameOverState.cpp
)

# View
set(ViewSources
        ${CMAKE_CURRENT_SOURCE_DIR}/view/Starfield.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/view/TextureManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/view/Explosion.cpp
)

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
