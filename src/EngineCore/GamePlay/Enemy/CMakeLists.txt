add_subdirectory(Fang)
add_subdirectory(Perception)

set(ENEMY_SRC
        ${FANG_SRC}
        ${PERCEPTION_SRC}

        PARENT_SCOPE
)