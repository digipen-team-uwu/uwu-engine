#Populate source file cache
file(GLOB_RECURSE SOURCE *.cpp)

set(SOURCE ${SOURCE} PARENT_SCOPE)
