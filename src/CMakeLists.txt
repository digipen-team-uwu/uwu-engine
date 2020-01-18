#Populate source file cache
add_subdirectory(EngineCore)
add_subdirectory(Executable)
add_subdirectory(Tests)

set(EXECUTABLE_SRC ${EXECUTABLE_SRC} PARENT_SCOPE)
set(ENGINE_CORE_SRC ${ENGINE_CORE_SRC} PARENT_SCOPE)
set(TESTS_SRC ${TESTS_SRC} PARENT_SCOPE)
