cmake_minimum_required(VERSION 3.10)

project(uwuEngine)

#Global include directory for all builds
include_directories(include)

#Add sub directories
add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(src)

#Add and Configure Engine executable
add_executable(uwuEngine ${HEADERS} ${SOURCE})
set_property(TARGET uwuEngine PROPERTY CXX_STANDARD 17)
if (MSVC)
    target_compile_definitions(uwuEngine PUBLIC _MSVC)
endif ()

target_include_directories(uwuEngine PUBLIC ${FMOD_INCLUDE_DIR})
target_include_directories(uwuEngine PUBLIC ${GLEW_INCLUDE_DIR})

target_link_libraries(uwuEngine
        opengl32
        glu32
        ${FMOD_LIBRARY}
        ${FSBANK_LIBRARY}
        ${FMOD_STUDIO_LIBRARY}
        libglew_static
        glfw
        GLM
        L_IMGUI
        MAGIC_ENUM
        RAPID_JSON
        RECTPACK2D
        STB
        L_SPINE_C
        )

# Copy FMOD dll
add_custom_command(TARGET uwuEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FMOD_DLL}
        $<TARGET_FILE_DIR:uwuEngine>)

# Copy Data folder
file(COPY
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_SOURCE_DIR}/assets
        ${PROJECT_SOURCE_DIR}/logs
        ${PROJECT_SOURCE_DIR}/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
