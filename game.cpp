#include "roguelike.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Инициализация SFML и создание окна
    sf::RenderWindow window(sf::VideoMode(640, 480), "Roguelike");

    // Создаем объекты
    Player player(100, 20, 5, 0, 1, true, 1, 1);
    Dungeon dungeon(20, 15); // Создай подземелье
    dungeon.generate(); // Сгенерируй подземелье

    // Игровой цикл
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Логика игры
        // ... (например, обработка ввода, движение игрока, проверка столкновений)

        // Отрисовка игры
        window.clear(); // Очистка экрана
        // ... (например, отрисовка игрока, врагов, предметов и т.д.)
        window.display(); // Отображение изменений на экране
    }

    return 0;
}