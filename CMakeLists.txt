cmake_minimum_required(VERSION 3.10)
project(STHFighter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SDL3 Path
set(CMAKE_PREFIX_PATH "C:/SDL3/lib/cmake")
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Include directories
include_directories("${CMAKE_SOURCE_DIR}/SDL-release-3.2.8/include")
include_directories("${CMAKE_SOURCE_DIR}/src")  # Include your source folder

# Add all source files
add_executable(sthfighter 
    src/core/main.cpp 
    src/core/Game.cpp  # Add Game.cpp here
    src/core/Player.cpp 
    src/characters/milia_rage.cpp 
    src/characters/axl_low.cpp 
 
)

# Link SDL3
target_link_libraries(sthfighter PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
