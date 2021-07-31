cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project3)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/38658/Desktop/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp toolClass.cpp toolClass.h tile.cpp tile.h displayManager.cpp displayManager.h MouseController.cpp MouseController.h controlImage.cpp controlImage.h logicController.cpp logicController.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)