#Populate source file cache
add_subdirectory(EngineCore)
add_subdirectory(Executable)
add_subdirectory(Tests)
add_subdirectory(PonderTest)

set(EXECUTABLE_SRC ${EXECUTABLE_SRC} PARENT_SCOPE)
set(ENGINE_CORE_SRC ${ENGINE_CORE_SRC} PARENT_SCOPE)
set(TESTS_SRC ${TESTS_SRC} PARENT_SCOPE)
set(PONDER_TEST_SRC ${PONDER_TEST_SRC} PARENT_SCOPE)
