#pragma once
#ifndef ROGUELIKE_H
#define ROGUELIKE_H

#include <SFML/Graphics.hpp> // Включаем SFML для работы с графикой

class Player; // Объявляем класс Player
class Enemy; // Объявляем класс Enemy
class Item; // Объявляем класс Item
class Dungeon; // Объявляем класс Dungeon

// Объявляем функции
void levelUp(Player& player); // Функция повышения уровня
Enemy* randomEnemy(const std::vector<Enemy*>& enemies);
Item* randomDrop(const std::vector<Item*>& items);

#endif 