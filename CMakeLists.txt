cmake_minimum_required(VERSION 3.10)
project(RoguelikeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED system window graphics network audio)

add_executable(RoguelikeGame main.cpp Player.cpp Enemy.cpp Item.cpp Dungeon.cpp)

target_link_libraries(RoguelikeGame sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

target_include_directories(RoguelikeGame PRIVATE ${SFML_INCLUDE_DIR})
