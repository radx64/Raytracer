file(GLOB_RECURSE SRC
    "./*.cc"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_definitions(-pthread)
add_definitions(-std=c++17)
add_definitions(-O0)

add_library(gtest ${SRC})