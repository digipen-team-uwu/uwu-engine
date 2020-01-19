add_subdirectory(Lighting)
add_subdirectory(Shader)
add_subdirectory(SpineAnimation)
add_subdirectory(Texture)

set(GRAPHICS_SRC
        ${LIGHTING_SRC}
        ${SHADER_SRC}
        ${SPINE_ANIMATION_SRC}
        ${TEXTURE_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Instances.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Render.cpp

        PARENT_SCOPE
)