# Let Sub modules build themselves
add_subdirectory(glfw)
add_subdirectory(rttr)

option (glew-cmake_BUILD_SHARED "Build shared libraries" ON)
set(glew-cmake_BUILD_SHARED OFF)
option(glew-cmake_BUILD_MULTI_CONTEXT "Build the multi context glew library" ON)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF)
add_subdirectory(glew)
#############################################################################
# Find libraries that are in binary
# Find FMOD
if (WIN32)
    set(FMOD_INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/core/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/fsbank/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/studio/inc
            PARENT_SCOPE)

    if (MSVC)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            find_library(FMOD_LIBRARY
                    NAMES
                    fmodL_vc
                    PATHS
                    FMOD/Win32/core/lib/x64)
            find_library(FSBANK_LIBRARY
                    NAMES
                    fsbank_vc
                    PATHS
                    FMOD/Win32/fsbank/lib/x64)
            find_library(FMOD_STUDIO_LIBRARY
                    NAMES
                    fmodstudioL_vc
                    PATHS
                    FMOD/Win32/studio/lib/x64)
            set(FMOD_DLL
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/core/lib/x64/fmodL.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/fsbank/lib/x64/fsbank.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/studio/lib/x64/fmodstudioL.dll
                    PARENT_SCOPE)
        else()
            find_library(FMOD_LIBRARY
                    NAMES
                    fmod_vc
                    PATHS
                    FMOD/Win32/core/lib/x64)
            find_library(FSBANK_LIBRARY
                    NAMES
                    fsbank_vc
                    PATHS
                    FMOD/Win32/fsbank/lib/x64)
            find_library(FMOD_STUDIO_LIBRARY
                    NAMES
                    fmodstudio_vc
                    PATHS
                    FMOD/Win32/studio/lib/x64)
            set(FMOD_DLL
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/core/lib/x64/fmod.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/fsbank/lib/x64/fsbank.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/studio/lib/x64/fmodstudio.dll
                    PARENT_SCOPE)
        endif()
    else ()
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            find_library(FMOD_LIBRARY
                    NAMES
                    fmodL
                    PATHS
                    FMOD/Win32/core/lib/x64)
            find_library(FSBANK_LIBRARY
                    NAMES
                    fsbank
                    PATHS
                    FMOD/Win32/fsbank/lib/x64)
            find_library(FMOD_STUDIO_LIBRARY
                    NAMES
                    fmodstudioL
                    PATHS
                    FMOD/Win32/studio/lib/x64)
            set(FMOD_DLL
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/core/lib/x64/fmodL.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/fsbank/lib/x64/fsbank.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/studio/lib/x64/fmodstudioL.dll
                    PARENT_SCOPE)
        else()
            find_library(FMOD_LIBRARY
                    NAMES
                    fmod
                    PATHS
                    FMOD/Win32/core/lib/x64)
            find_library(FSBANK_LIBRARY
                    NAMES
                    fsbank
                    PATHS
                    FMOD/Win32/fsbank/lib/x64)
            find_library(FMOD_STUDIO_LIBRARY
                    NAMES
                    fmodstudio
                    PATHS
                    FMOD/Win32/studio/lib/x64)
            set(FMOD_DLL
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/core/lib/x64/fmod.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/fsbank/lib/x64/fsbank.dll
                    ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Win32/studio/lib/x64/fmodstudio.dll
                    PARENT_SCOPE)
        endif()
    endif ()
endif ()

if (UNIX)
    set(FMOD_INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Linux/core/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Linux/fsbank/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/FMOD/Linux/studio/inc
            PARENT_SCOPE)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_library(FMOD_LIBRARY
                NAMES
                fmodL
                PATHS
                FMOD/Linux/core/lib/x86_64)
        find_library(FSBANK_LIBRARY
                NAMES
                fsbank
                PATHS
                FMOD/Linux/fsbank/lib/x86_64)
        find_library(FMOD_STUDIO_LIBRARY
                NAMES
                fmodstudioL
                PATHS
                FMOD/Linux/studio/lib/x86_64)
        #TODO:: Copy Fmod shared library
    else()
        find_library(FMOD_LIBRARY
                NAMES
                fmod
                PATHS
                FMOD/Linux/core/lib/x86_64)
        find_library(FSBANK_LIBRARY
                NAMES
                fsbank
                PATHS
                FMOD/Linux/fsbank/lib/x86_64)
        find_library(FMOD_STUDIO_LIBRARY
                NAMES
                fmodstudio
                PATHS
                FMOD/Linux/studio/lib/x86_64)
        #TODO:: Copy Fmod shared library
    endif()
endif ()

#############################################################################
# Find Header only libraries
# Find Catch2
set(CATCH2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch2/single_include)
add_library(CATCH2 INTERFACE)
target_include_directories(CATCH2 INTERFACE ${CATCH2_INCLUDE_DIR})

# Find GLM
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glm)
add_library(GLM INTERFACE)
target_include_directories(GLM INTERFACE ${GLM_INCLUDE_DIR})

# Find magic_enum
set(MAGIC_ENUM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/magic_enum/include)
add_library(MAGIC_ENUM INTERFACE)
target_include_directories(MAGIC_ENUM INTERFACE ${MAGIC_ENUM_INCLUDE_DIR})

# Find rapidjson
#TODO::fix rapidjson include directory
set(RAPID_JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)
add_library(RAPID_JSON INTERFACE)
target_include_directories(RAPID_JSON INTERFACE ${RAPID_JSON_INCLUDE_DIR})

# Find rectpack2D
set(RECTPACK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rectpack2D/src)
add_library(RECTPACK2D INTERFACE)
target_include_directories(RECTPACK2D INTERFACE ${RECTPACK_INCLUDE_DIR})

# Find stb
set(STB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb)
add_library(STB INTERFACE)
target_include_directories(STB INTERFACE ${STB_INCLUDE_DIR})

#############################################################################
# Build libraries from source
# Build IMGUI
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui ${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples)
file(GLOB IMGUI_SRC "imgui/*.cpp")
# Append IMGUI SRC with openGL and GLFW
set(IMGUI_SRC
        ${IMGUI_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/examples/imgui_impl_opengl3.cpp)
add_library(L_IMGUI ${IMGUI_SRC})
target_include_directories(L_IMGUI
        PUBLIC
        ${IMGUI_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        )
target_link_libraries(L_IMGUI
        PRIVATE
        glfw
        libglew_static
)

# Build spine c runtime
set(SPINE_C_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/spine-c/include)
file(GLOB SPINE_SRC "spine-c/src/*.c")
add_library(L_SPINE_C ${SPINE_SRC})
target_link_libraries(L_SPINE_C UWU_ENGINE_CORE)
target_include_directories(L_SPINE_C
        PUBLIC
        ${SPINE_C_INCLUDE_DIR}
        )
