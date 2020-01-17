add_subdirectory(Enemy)
add_subdirectory(Player)

set(GAME_PLAY_SRC
        ${PLAYER_SRC}
        ${ENEMY_SRC}

        PARENT_SCOPE
)