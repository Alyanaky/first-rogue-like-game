#include "roguelike.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // ������������� SFML � �������� ����
    sf::RenderWindow window(sf::VideoMode(640, 480), "Roguelike");

    // ������� �������
    Player player(100, 20, 5, 0, 1, true, 1, 1);
    Dungeon dungeon(20, 15); // ������ ����������
    dungeon.generate(); // ���������� ����������

    // ������� ����
    while (window.isOpen()) {
        // ��������� �������
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // ������ ����
        // ... (��������, ��������� �����, �������� ������, �������� ������������)

        // ��������� ����
        window.clear(); // ������� ������
        // ... (��������, ��������� ������, ������, ��������� � �.�.)
        window.display(); // ����������� ��������� �� ������
    }

    return 0;
}