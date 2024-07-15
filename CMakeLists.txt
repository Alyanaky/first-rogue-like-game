cmake_minimum_required(VERSION 3.10)
project(roguelike)

set(CMAKE_CXX_STANDARD 17)

# Добавляем библиотеки SFML
find_package(SFML REQUIRED graphics window system)

# Добавляем файлы исходного кода
add_executable(roguelike main.cpp player.cpp enemy.cpp item.cpp dungeon.cpp game.cpp)

target_link_libraries(roguelike ${SFML_LIBRARIES})