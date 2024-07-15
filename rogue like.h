#pragma once
#ifndef ROGUELIKE_H
#define ROGUELIKE_H

#include <SFML/Graphics.hpp> // �������� SFML ��� ������ � ��������

class Player; // ��������� ����� Player
class Enemy; // ��������� ����� Enemy
class Item; // ��������� ����� Item
class Dungeon; // ��������� ����� Dungeon

// ��������� �������
void levelUp(Player& player); // ������� ��������� ������
Enemy* randomEnemy(const std::vector<Enemy*>& enemies);
Item* randomDrop(const std::vector<Item*>& items);

#endif 