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
add_library(UWU_ENGINE_CORE ${HEADERS} ${ENGINE_CORE_SRC})
add_executable(Umbra ${EXECUTABLE_SRC})
add_executable(uwuEditor ${EXECUTABLE_SRC})
add_executable(uwuTest ${TESTS_SRC})

target_compile_definitions(uwuEditor PUBLIC _Editor)
set_property(TARGET UWU_ENGINE_CORE Umbra uwuEditor PROPERTY CXX_STANDARD 17)

if (MSVC)
    target_compile_definitions(UWU_ENGINE_CORE PUBLIC _MSVC)
    target_compile_definitions(Umbra PUBLIC _MSVC)
    target_compile_definitions(uwuEditor PUBLIC _MSVC)
else ()
    add_compile_options(UWU_ENGINE_CORE -g)
    add_compile_options(Umbra -g)
    add_compile_options(uwuEditor -g)
    target_compile_definitions(UWU_ENGINE_CORE PUBLIC _GLIBCXX_DEBUG)
    target_compile_definitions(Umbra PUBLIC _GLIBCXX_DEBUG)
    target_compile_definitions(uwuEditor PUBLIC _GLIBCXX_DEBUG)
endif()

target_include_directories(UWU_ENGINE_CORE PUBLIC ${FMOD_INCLUDE_DIR})


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("we in debug mode")
    target_compile_definitions(UWU_ENGINE_CORE PUBLIC _DEBUG)
    target_compile_definitions(Umbra PUBLIC _DEBUG)
    target_compile_definitions(uwuEditor PUBLIC _DEBUG)
endif()

#Populate library list
set(UWU_LIBS
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

#Extend compiler/OS specific libs
if (MSVC)
    set(UWU_LIBS
        ${UWU_LIBS}
        opengl32
        glu32
    )
else ()
    set(UWU_LIBS
        ${UWU_LIBS}
        OpenGL
        GLX
        stdc++fs
    )
endif ()

#Link targets with libraries
target_link_libraries(UWU_ENGINE_CORE ${UWU_LIBS})
target_link_libraries(Umbra UWU_ENGINE_CORE)
target_link_libraries(uwuEditor UWU_ENGINE_CORE)
target_link_libraries(uwuTest UWU_ENGINE_CORE CATCH2)

# Copy FMOD dll
if (WIN32)
add_custom_command(TARGET Umbra POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FMOD_DLL}
        $<TARGET_FILE_DIR:Umbra>)
add_custom_command(TARGET uwuEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${FMOD_DLL}
        $<TARGET_FILE_DIR:uwuEditor>)
endif ()

# Copy Data folder
file(COPY
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
