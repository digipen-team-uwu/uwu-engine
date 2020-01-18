#Populate source file cache
file(GLOB_RECURSE TESTS_SRC *.cpp)

set(TESTS_SRC ${TESTS_SRC} PARENT_SCOPE)
