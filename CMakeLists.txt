cmake_minimum_required(VERSION 3.10)

#Use modern OpenGL libraries instead of legacy ones
set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

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

if (MSVC)
    target_link_libraries(uwuEngine
            opengl32
            glu32
            )
else ()
    target_link_libraries(uwuEngine
            OpenGL
            GLX
            stdc++fs
            )
endif ()

target_link_libraries(uwuEngine
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
if (WIN32)
add_custom_command(TARGET uwuEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FMOD_DLL}
        $<TARGET_FILE_DIR:uwuEngine>)
endif ()

# Copy Data folder
file(COPY
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
