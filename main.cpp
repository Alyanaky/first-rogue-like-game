#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <conio.h>
#include <queue>
#include <ctime>
#include <fstream>
using namespace std;
using namespace sf;




// Класс игрока
class Player {
private:
    int health;  // Здоровье игрока
    int strength; // Сила игрока, влияющая на урон
    int experience; // Опыт игрока, накапливается при победе над врагами
    int defense;  // Защита игрока, снижает получаемый урон
    int level; // Уровень
    bool life;
    int x, y; // Координаты игрока
public:
    // Конструктор: Инициализирует характеристики при создании объекта Player
    Player(int hp, int str, int def, int exp, int lvl, bool lf, int xCoord, int yCoord) :
        health(hp), strength(str), defense(def), experience(exp), level(lvl), life(lf), x(xCoord), y(yCoord) {}

    // Методы "getter" (получение значений): Возвращают текущее значение характеристики
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    int getExperience() const { return experience; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    bool getLife() const { return life; }
    int getX() const { return x; }
    int getY() const { return y; }

    // Методы "setter" (установка значений): Изменяют значение характеристики
    void setHealth(int newHealth) { health = newHealth; }
    void setStrength(int newStrength) { strength = newStrength; }
    void setExperience(int newExperience) { experience = newExperience; }
    void setDefense(int newDefense) { defense = newDefense; }
    void setLevel(int newLevel) { level = newLevel; }
    void setLife(bool newLife) { life = newLife; }
    void setPosition(int xCoord, int yCoord) {
    }
    // Метод для получения урона
    void takeDamage(int damage) {
        health -= (damage - defense);  // Учитываем защиту при получении урона
        if (health <= 0) {
            life = false;
            // Здесь можно добавить логику окончания игры
        }
    }
    void move(int dx, int dy, const vector<vector<char>>& map) {
        if (x + dx < 1 || x + dx >= map[0].size() ||
            y + dy < 1 || y + dy >= map.size()) {
            return; // Блокируем движение
        }
        if (map[y + dy][x + dx] != '#') {
            x += dx;
            y += dy;
        }
    }
};

// Класс врага
class Enemy {
private:
    string name; // Имя врага
    int health; // Здоровье врага
    int atack; // Урон, который враг наносит игроку
    bool life = true;
    int experienceReward; // Количество опыта, которое игрок получает за победу над врагом
    RectangleShape shape; // Форма врага для отрисовки
    int x, y; // Координаты врага
public:
    // Конструктор
    Enemy(const string& enemyName, int hp, int atk, int expReward, int xCoord, int yCoord) :
        name(enemyName), health(hp), atack(atk), experienceReward(expReward), x(xCoord), y(yCoord) {
        shape.setSize(Vector2f(32, 32)); // Размер формы врага
        shape.setFillColor(Color::Red); // Цвет формы врага
        shape.setPosition(x * 32, y * 32); // Позиция формы врага
    }

    // Геттеры для получения информации о враге
    const string& getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return atack; }
    bool getLife() const { return life; }
    int getExperienceReward() const { return experienceReward; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // Метод для получения урона врагом
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            life = false;
        }
    }

    // Метод для нанесения урона врагом игроку
    void attack(Player& player) const {
        player.takeDamage(atack);
    }

    void setPosition(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
        shape.setPosition(x * 32, y * 32);
    }
};

// Класс предмета
class Item {
private:
    string name; // Название предмета
    int damageBonus; // Бонус к урону, который дает предмет (может быть отрицательным для брони)
    int defenseBonus; // Бонус к защите, который дает предмет (может быть отрицательным для оружия)
    int heal;
    int damageToPlayer;
    RectangleShape shape; // Форма предмета для отрисовки
    int x, y; // Координаты предмета
public:
    // Конструктор
    Item(const string& itemName, int damage = 0, int defense = 0, int HEALcount = 0, int DTP = 0, int xCoord = 0, int yCoord = 0) :
        name(itemName), damageBonus(damage), defenseBonus(defense), heal(HEALcount), damageToPlayer(DTP), x(xCoord), y(yCoord) {
        shape.setSize(Vector2f(32, 32)); // Размер формы предмета
        shape.setFillColor(Color::Green); // Цвет формы предмета
        shape.setPosition(x * 32, y * 32); // Позиция формы предмета
    }

    // Геттеры для получения информации о предмете
    const string& getName() const { return name; }

    int getDamageBonus() const { return damageBonus; }
    int getDefenseBonus() const { return defenseBonus; }
    int getHeal() const { return heal; }
    int getDamageToPlayer() const { return damageToPlayer; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // Метод для применения эффекта предмета к игроку
    void applyEffect(Player& player) const {
        player.setStrength(player.getStrength() + damageBonus);
        player.setDefense(player.getDefense() + defenseBonus);
        player.setHealth(player.getHealth() + heal);
    }

    // Метод для удаления эффекта предмета от игрока
    void removeEffect(Player& player) const {
        player.setStrength(player.getStrength() - damageBonus);
        player.setDefense(player.getDefense() - defenseBonus);
    }

    void setPosition(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
        shape.setPosition(x * 32, y * 32);
    }
};

// Функция для случайного выпадения предмета
Item* randomDrop(const vector<Item*>& items) {
    if (items.empty()) {
        return nullptr; // Если массив пуст, ничего не выпадает
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, items.size() - 1);
    int randomIndex = distrib(gen);
    return items[randomIndex]; // Возвращаем случайный предмет
}

// Функция для случайного выбора врага
Enemy* randomEnemy(const vector<Enemy*>& enemies) {
    if (enemies.empty()) {
        return nullptr; // Если массив пуст, ничего не выпадает
    }

    if (enemies.empty()) {
        return nullptr; // Если массив пуст, ничего не выпадает
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, enemies.size() - 1);
    int randomIndex = distrib(gen);

    return enemies[randomIndex]; // Возвращаем случайного врага
}

// Функция для повышения уровня игрока
void levelUp(Player& player) {
    if (player.getExperience() >= 100) {
        player.setLevel(2);
        player.setHealth(player.getHealth() + 10);
        player.setStrength(player.getStrength() + 10);
        player.setDefense(player.getDefense() + 2);
    }
    else if (player.getExperience() >= 300) {
        player.setLevel(3);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }
    else if (player.getExperience() >= 400) {
        player.setLevel(4);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }
    else if (player.getExperience() >= 500) {
        player.setLevel(5);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }

}

class Dungeon {
private:
    int width;
    int height;
    int stairUpX = random(1, width - 1);
    int stairUpY = random(1, height - 1);
    int stairDownX = random(1, height - 1);
    int stairDownY = random(1, height - 1);
    vector<vector<char>> map;

    // Генерация случайного числа в заданном диапазоне
    int random(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }

    // Алгоритм клеточного автомата
    void generateCellularAutomaton(int iterations) {
        // Заполняем карту случайными клетками (стенa/пол)
        // (изменение: 60% стен вместо 40%)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (random(0, 100) < 80) {
                    map[y][x] = '#'; // Стена
                }
                else {
                    map[y][x] = '.'; // Пол
                }
            }
        }

        // Итерации клеточного автомата
        for (int i = 0; i < iterations; ++i) {
            // Создаем временную карту
            vector<vector<char>> tempMap = map;

            // Проходимся по каждой клетке
            for (int y = 1; y < height - 1; ++y) {
                for (int x = 1; x < width - 1; ++x) {
                    // Считаем живых соседей
                    int liveNeighbours = countLiveNeighbours(x, y);

                    // Применяем правила клеточного автомата
                    if (map[y][x] == '#' && (liveNeighbours < 0 || liveNeighbours > 5)) {
                        tempMap[y][x] = '.'; // Умирает
                    }
                    else if (map[y][x] == '.' && liveNeighbours == 3) {
                        tempMap[y][x] = '#'; // Рождается
                    }
                }
            }

            // Обновляем карту
            map = tempMap;
        }
    }

    // Подсчет живых соседей для клетки
    int countLiveNeighbours(int x, int y) {
        int count = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) {
                    continue; // Не считаем клетку
                }
                if (map[y + dy][x + dx] == '#') {
                    count++;
                }
            }
        }
        return count;
    }

    // Создание коридоров
    void createCorridors() {
        // Проходимся по карте, ищем места для коридоров
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                if (map[y][x] == '.' &&
                    (map[y - 1][x] == '#' || map[y + 1][x] == '#' ||
                        map[y][x - 1] == '#' || map[y][x + 1] == '#')) {
                    // Находим точку входа/выхода
                    int direction = random(0, 3);
                    switch (direction) {
                    case 0: if (map[y - 1][x] == '#') { map[y - 1][x] = '.'; } break;
                    case 1: if (map[y + 1][x] == '#') { map[y + 1][x] = '.'; } break;
                    case 2: if (map[y][x - 1] == '#') { map[y][x - 1] = '.'; } break;
                    case 3: if (map[y][x + 1] == '#') { map[y][x + 1] = '.'; } break;
                    }
                }
            }
        }
    }
    // Функция для создания комнаты в заданных координатах
    void createRoom(int x, int y, int width, int height) {
        for (int row = y; row < y + height; ++row) {
            for (int col = x; col < x + width; ++col) {
                if (row >= 0 && row < height && col >= 0 && col < width) {
                    map[row][col] = '.';
                }
            }
        }
    }
    // Функция для поиска пустых областей
    vector<pair<int, int>> findEmptyAreas() {
        vector<pair<int, int>> emptyAreas;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (map[y][x] == '.') {
                    // Проверяем, что клетка не граничит с другой пустой областью
                    if (x > 0 && map[y][x - 1] == '#' &&
                        x < width - 1 && map[y][x + 1] == '#' &&
                        y > 0 && map[y - 1][x] == '#' &&
                        y < height - 1 && map[y + 1][x] == '#') {
                        emptyAreas.push_back(make_pair(x, y));
                    }
                }
            }
        }
        return emptyAreas;
    }
    void createCorridorBetweenRooms(pair<int, int> room1, pair<int, int> room2) {
        int x1 = (room1.first * 2 + 1) * (width / 10);
        int y1 = (room1.second * 2 + 1) * (height / 10);
        int x2 = (room2.first * 2 + 1) * (width / 10);
        int y2 = (room2.second * 2 + 1) * (height / 10);

        while (x1 != x2 || y1 != y2) {
            if (x1 < x2) {
                x1++;
            }
            else if (x1 > x2) {
                x1--;
            }
            else if (y1 < y2) {
                y1++;
            }
            else {
                y1--;
            }
            map[y1][x1] = '.';
        }
    }

    void createCorridorsBetweenRooms() {
        for (int i = 0; i < height / 10; i++) {
            for (int j = 0; j < width / 10; j++) {
                if (i % 2 == 1 && j % 2 == 1) {
                    if (j + 1 < width / 10) {
                        createCorridorBetweenRooms({ i, j }, { i, j + 1 });
                    }
                    if (i + 1 < height / 10) {
                        createCorridorBetweenRooms({ i, j }, { i + 1, j });
                    }
                }
            }
        }
    }



    // Создаем коридоры между комнатами (горизонтальные)
    void createPredefinedCorridors() {
        for (int y = 0; y < height; y += 2) {
            for (int x = 0; x < width; x++) {
                if (x % 10 == 0 && map[y][x] == '#' && map[y][x + 1] == '#') {
                    map[y][x] = '.';
                    map[y][x + 1] = '.';
                    x += 2; // Переходим к следующей "паре" клеток
                }
            }
        }
    }

    // Создаем коридоры между комнатами (вертикальные)
    void createPredefinedCorridors2() {
        int r = random(1, height);
        for (int x = 0; x < width; x++) {
            map[r][x] = '.';
        }
    }
    void createPredefinedCorridors3() {
        int r = random(1, height);
        for (int x = 0; x < width; x++) {
            map[r][x] = '.';
        }
    }
    void createPredefinedCorridors4() {
        int r = random(1, height);
        for (int x = 0; x < width; x++) {
            map[r][x] = '.';
        }
    }
    void createPredefinedCorridors5() {
        int r = random(1, width);
        for (int x = 0; x < height; x++) {
            map[x][r] = '.';
        }
    }

    // Создаем комнаты (просто прямоугольники)
    void createPredefinedRooms() {
        createRoom(2, 2, 10, 12); //  Комната 1
        createRoom(width / 2 - 3, height / 2 - 3, 10, 10); // Комната 2
        createRoom(width - 6, height - 6, 12, 13); // Комната 3
    }



public:
    Dungeon(int w, int h) : width(w), height(h) {
        map.resize(height, vector<char>(width, '#'));
    }
    // Геттеры
    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }
    int getUpstairX() {
        return stairUpX;
    }
    int getUpstairY() {
        return stairUpY;
    }
    int getDownstairX() {
        return stairDownX;
    }
    int getDownstairY() {
        return stairDownY;
    }

    // Сеттеры
    void setWidth(int a) {
        width = a;
    }
    void setHeight(int a) {
        height = a;
    }
    /*
    bool isPathBetweenStairs(int stairUpX, int stairUpY, int stairDownX, int stairDownY) {
        // Реализуй поиск в ширину (BFS) или другой алгоритм поиска пути
        // Используй map для проверки, доступна ли клетка для прохода
        // Возвращай true, если найден путь, и false, если нет пути
        // Создаем очередь для поиска в ширину (BFS)
        queue<pair<int, int>> queue;
        // Добавляем начальную клетку "stairUp" в очередь
        queue.push(make_pair(stairUpX, stairUpY));

        // Создаем массив посещенных клеток
        vector<vector<bool>> visited(height, vector<bool>(width, false));
        // Помечаем стартовую клетку как посещенную
        visited[stairUpY][stairUpX] = true;

        // Пока очередь не пуста
        while (!queue.empty()) {
            // Извлекаем клетку из очереди
            pair<int, int> current = queue.front();
            queue.pop();

            // Если мы добрались до "stairDown" - путь найден
            if (current.first == stairDownX && current.second == stairDownY) {
                return true;
            }

            // Проверяем соседние клетки
            int dx[] = { 0, 1, 0, -1 }; //  Горизонтальные смещения
            int dy[] = { 1, 0, -1, 0 }; // Вертикальные смещения

            for (int i = 0; i < 4; ++i) {
                int nextX = current.first + dx[i];
                int nextY = current.second + dy[i];

                // Проверяем, находится ли соседняя клетка в пределах карты
                if (nextX >= 0 && nextX < width && nextY >= 0 && nextY < height) {
                    // Проверяем, доступна ли соседняя клетка (проход или лестница)
                    if (map[nextY][nextX] == '.' || map[nextY][nextX] == 'U' || map[nextY][nextX] == 'D') {
                        // Если клетка не посещена - добавляем ее в очередь
                        if (!visited[nextY][nextX]) {
                            queue.push(make_pair(nextX, nextY));
                            visited[nextY][nextX] = true;
                        }
                    }
                }
            }
        }

        // Если очередь опустела, не найдя "stairDown" - пути нет
        return false;
    }
    */
    
    // Генерация подземелья
    void generate(int level) {
        // Используем клеточный автомат для базовой генерации
        generateCellularAutomaton(10); // 10 итераций
        createPredefinedRooms();
        createPredefinedCorridors();
        createPredefinedCorridors2();
        createPredefinedCorridors3();
        createPredefinedCorridors4();
        createPredefinedCorridors5();// Добавляем вертикальные коридоры
        createCorridorsBetweenRooms();


        map[stairUpY][stairUpX] = 'U';

        int stairDownX = random(1, width - 1);
        int stairDownY = random(1, height - 1);
        map[stairDownY][stairDownX] = 'D';

        // Проверяем, есть ли проход между ними
      /*  while (!isPathBetweenStairs(stairUpX, stairUpY, stairDownX, stairDownY)) {
            // Если нет, переносим "stairDown" в другое место
            stairDownX = random(1, width - 1);
            stairDownY = random(1, height - 1);
            map[stairDownY][stairDownX] = 'D';
        }*/
        //раскид предметов
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (map[y][x] == '.') { // Если клетка пустая
                    if (random(1, 50) == 5) {
                        map[y][x] = 'I';
                    }
                }
            }
        }

    }

    // Метод для получения карты подземелья
    vector<vector<char>> getMap(){
    return map;
    }

};


int main() {

    // Установка региональных настроек для русского языка
    setlocale(LC_ALL, "Russian");
    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // ===============================================================================
    // Создание массива предметов
    // Оружие
    vector<Item*> items;
    items.push_back(new Item("Меч", 30, 0, 0, 0, 2, 3));
    items.push_back(new Item("Булава", 20, 0, 0, 0, 4, 5));
    items.push_back(new Item("Копье", 40, 0, 0, 0, 6, 2));
    items.push_back(new Item("Двуручный меч", 60, 0, 0, 0, 8, 4));
    items.push_back(new Item("Кинжал", 15, 0, 0, 0, 10, 1));
    items.push_back(new Item("Топор", 40, 0, 0, 0, 5, 3));

    // Доспехи
    items.push_back(new Item("Щит", 0, 10, 0, 0, 2, 5));
    items.push_back(new Item("Доспех", 0, 40, 0, 0, 4, 2));
    items.push_back(new Item("Кожаная броня", 0, 5, 0, 0, 6, 5));
    items.push_back(new Item("Кольчуга", 0, 15, 0, 0, 8, 3));
    items.push_back(new Item("Пластинчатая броня", 0, 25, 0, 0, 10, 2));
    items.push_back(new Item("Шлем", 0, 5, 0, 0, 5, 4));

    // Прочее
    items.push_back(new Item("Еда", 0, 0, 10, 0, 2, 2));
    items.push_back(new Item("Питьевая вода", 0, 0, 5, 0, 4, 4));
    items.push_back(new Item("Зелье лечения", 0, 0, 20, 0, 6, 1));
    items.push_back(new Item("Подозрительное зелье", 0, 0, 0, 30, 8, 2));

    // ===============================================================================
    // Создание массива врагов
    vector<Enemy*> enemies;
    // Слабые противники 1 - 9
    enemies.push_back(new Enemy("Крыса", 20, 5, 10, 2, 2));
    enemies.push_back(new Enemy("Паук", 15, 3, 8, 4, 4));
    enemies.push_back(new Enemy("Гоблин", 25, 7, 15, 6, 3));
    enemies.push_back(new Enemy("Волк", 30, 10, 18, 8, 1));
    enemies.push_back(new Enemy("Скелет", 40, 30, 30, 10, 4));
    enemies.push_back(new Enemy("Зомби", 35, 15, 25, 5, 5));
    enemies.push_back(new Enemy("Нежить", 28, 12, 20, 2, 4));
    enemies.push_back(new Enemy("Бандит", 32, 18, 22, 4, 1));
    enemies.push_back(new Enemy("Бешеный волк", 45, 15, 28, 6, 4));

    // Средние противники 10 - 20
    enemies.push_back(new Enemy("Зомби", 50, 25, 35, 8, 3));
    enemies.push_back(new Enemy("Огр", 60, 25, 40, 10, 2));
    enemies.push_back(new Enemy("Тролль", 70, 30, 50, 5, 2));
    enemies.push_back(new Enemy("Голем", 80, 40, 60, 2, 5));
    enemies.push_back(new Enemy("Гриф", 55, 28, 45, 4, 3));
    enemies.push_back(new Enemy("Ведьма", 50, 20, 35, 6, 2));
    enemies.push_back(new Enemy("Оборотень", 65, 35, 55, 8, 4));
    enemies.push_back(new Enemy("Дракон", 100, 50, 80, 10, 3));
    enemies.push_back(new Enemy("Демон", 75, 45, 65, 5, 4));
    enemies.push_back(new Enemy("Призрак", 40, 10, 30, 2, 1));

    // Сильные противники 21 - 30
    enemies.push_back(new Enemy("Ледяной голем", 120, 60, 100, 4, 2));
    enemies.push_back(new Enemy("Огненный демон", 110, 70, 90, 6, 5));
    enemies.push_back(new Enemy("Гидра", 150, 80, 120, 8, 2));
    enemies.push_back(new Enemy("Дракон-хранитель", 200, 100, 150, 10, 5));
    enemies.push_back(new Enemy("Древний голем", 180, 90, 130, 5, 3));
    enemies.push_back(new Enemy("Король гоблинов", 130, 75, 110, 2, 4));
    enemies.push_back(new Enemy("Лорд демонов", 160, 95, 140, 4, 5));
    enemies.push_back(new Enemy("Босс", 250, 120, 200, 6, 4));
    enemies.push_back(new Enemy("Финальный босс", 400, 150, 250, 8, 3));

    // ==================================================================\

    //Создание основных объектов
    //Отрисовка окна
    RenderWindow window(VideoMode(50 * 32, 30 * 32), "Game");
    window.setFramerateLimit(60);
    // Генерация карты
    Dungeon dungeon(50, 30);
    int currentLevel = 1;
    //while (dungeon.isPathBetweenStairs(dungeon.getUpstairX(), dungeon.getUpstairY(), dungeon.getDownstairX(), dungeon.getDownstairY())) {
        dungeon.generate(currentLevel);
    //}

    // Создание объекта игрока
    Player player(100, 20, 5, 0, 1, true, dungeon.getUpstairX(), dungeon.getUpstairY());




    // ==================================================================
    // Создаем фон для интерфейса
    RectangleShape interfaceBackground(Vector2f(150, window.getSize().y));
    interfaceBackground.setFillColor(Color(0, 0, 0, 150)); // Полупрозрачный черный
    interfaceBackground.setPosition(window.getSize().x - interfaceBackground.getSize().x, 0);
    // Создаем текст для имени игрока
    Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        cout << "Ошибка загрузки шрифта: arial.ttf" << endl;
        return 1;
    }
    Text playerNameText("Name: ", font, 16);
    playerNameText.setFillColor(Color::White);
    playerNameText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 10);

    // Создаем текст для характеристики "Здоровье"
    Text healthText("Health: ", font, 16);
    healthText.setFillColor(Color::White);
    healthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 40);

    // Создаем текст для характеристики "Сила"
    Text strengthText("Strenght: ", font, 16);
    strengthText.setFillColor(Color::White);
    strengthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 70);

    // Создаем текст для характеристики "Защита"
    Text defenseText("Defense: ", font, 16);
    defenseText.setFillColor(Color::White);
    defenseText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 100);

    // Создаем текст для уровня
    Text levelText("Level: ", font, 16);
    levelText.setFillColor(Color::White);
    levelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 130);

    // Создаем текст для оружия
    Text weaponText("Weapon: ", font, 16);
    weaponText.setFillColor(Color::White);
    weaponText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 160);

    // Создаем текст для уровня подземелья
    Text dungeonLevelText("Dungeon Level: 1", font, 16); // Начальный уровень 1
    dungeonLevelText.setFillColor(Color::White);
    dungeonLevelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 190);



    bool interfaceVisible = false;

    // ==================================================================
    // Создаем спрайты для символов
    Texture wallTexture;
    if (!wallTexture.loadFromFile("textures/wall.png")) {
        cout << "Ошибка загрузки изображения: wall.png" << endl;
        return 1;
    }
    Sprite wallSprite(wallTexture);
    wallSprite.setTextureRect(IntRect(0, 0, 32, 32)); // Размер тайла 

    Texture floorTexture;
    if (!floorTexture.loadFromFile("textures/floor.png")) {
        cout << "Ошибка загрузки изображения: floor.png" << endl;
        return 1;
    }
    Sprite floorSprite(floorTexture);
    floorSprite.setTextureRect(IntRect(0, 0, 32, 32)); // Размер тайла 

    Texture enemyTexture;
    if (!enemyTexture.loadFromFile("textures/enemy.png")) {
        cout << "Ошибка загрузки изображения: enemy.png" << endl;
        return 1;
    }
    Sprite enemySprite(enemyTexture);
    enemySprite.setTextureRect(IntRect(0, 0, 32, 32)); // Размер тайла 

    Texture itemTexture;
    if (!itemTexture.loadFromFile("textures/item.png")) {
        cout << "Ошибка загрузки изображения: item.png" << endl;
        return 1;
    }

    Texture stairUpTexture;
    if (!stairUpTexture.loadFromFile("textures/stairUp.png")) {
        cout << "Ошибка загрузки изображения" << endl;
    }
    Sprite stairUpSprite(stairUpTexture);
    stairUpSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture stairDownTexture;
    if (!stairDownTexture.loadFromFile("textures/stairDown.png")) {
        cout << "Ошибка загрузки изображения" << endl;
    }
    Sprite stairDownSprite(stairDownTexture);
    stairDownSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Sprite itemSprite(itemTexture);
    itemSprite.setTextureRect(IntRect(0, 0, 32, 32)); // Размер тайла 

    Texture playerTexture;
    if (!playerTexture.loadFromFile("textures/player.png")) {
        cout << "Ошибка загрузки спрайта игрока!" << endl;
        return 1;
    }
    Sprite playerSprite(playerTexture);
    playerSprite.setTextureRect(IntRect(0, 0, 32, 32));

    // ==================================================================\


    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case  Event::Closed:
                window.close();
                break;
            case  Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                break;
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Tab) {
                    interfaceVisible = !interfaceVisible; // Переключаем видимость
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    player.move(0, -1, dungeon.getMap());
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Down) {
                    player.move(0, +1, dungeon.getMap());
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left) {
                    player.move(-1, 0, dungeon.getMap());
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Right) {
                    player.move(+1, 0, dungeon.getMap());
                }
            }
            if (dungeon.getMap()[player.getY()][player.getX()] == 'D') {
                // Переход на следующий уровень
                currentLevel++;

                /*/ Генерируем новый уровень
                while (dungeon.isPathBetweenStairs(dungeon.getUpstairX(), dungeon.getUpstairY(), dungeon.getDownstairX(), dungeon.getDownstairY())) {
                    dungeon.generate(currentLevel);
                }
                */
                // Перемещаем игрока на новый уровень
                player.setPosition(dungeon.getUpstairX(), dungeon.getUpstairY());
            }
        }
        // Обработка нажатия клавиш

            // Очищаем экран
        window.clear(Color::Black);
        // Получаем карту
        vector<vector<char>> map = dungeon.getMap();
        // Отрисовка карты
        for (int y = 0; y < dungeon.getHeight(); y++) {
            for (int x = 0; x < dungeon.getWidth(); x++) {
                // Определяем тип тайла
                switch (map[y][x]) {
                case '#': // Стена
                    wallSprite.setPosition(x * 32, y * 32);
                    window.draw(wallSprite);
                    break;
                case '.': // Пол
                    floorSprite.setPosition(x * 32, y * 32);
                    window.draw(floorSprite);
                    break;
                case 'I': //Предмет
                    itemSprite.setPosition(x * 32, y * 32);
                    window.draw(itemSprite);
                    break;
                case 'U': // StairUp
                    floorSprite.setPosition(x * 32, y * 32);
                    window.draw(floorSprite);
                    break;
                case 'D': // StairDown
                    stairDownSprite.setPosition(x * 32, y * 32);
                    window.draw(stairDownSprite);
                    break;
                }
            }
        }
        window.draw(playerSprite);
        // Отрисовка границ
        for (int y = 0; y < dungeon.getHeight(); y++) {
            wallSprite.setPosition(0, y * 32);
            window.draw(wallSprite);
            wallSprite.setPosition((dungeon.getWidth() - 1) * 32, y * 32);
            window.draw(wallSprite);
        }
        for (int x = 0; x < dungeon.getWidth(); x++) {
            wallSprite.setPosition(x * 32, 0);
            window.draw(wallSprite);
            wallSprite.setPosition(x * 32, (dungeon.getHeight() - 1) * 32);
            window.draw(wallSprite);
        }
        // Обновляем текст с характеристиками игрока
        healthText.setString("Здоровье: " + to_string(player.getHealth()));
        strengthText.setString("Сила: " + to_string(player.getStrength()));
        defenseText.setString("Защита: " + to_string(player.getDefense()));
        levelText.setString("Уровень: " + to_string(player.getLevel()));
        dungeonLevelText.setString("Dungeon Level: " + to_string(currentLevel));
        if (interfaceVisible) {
            // Выдвигаем интерфейс
            interfaceBackground.setPosition(window.getSize().x - interfaceBackground.getSize().x, 0);
            playerNameText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 10);
            healthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 40);
            strengthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 70);
            defenseText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 100);
            levelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 130);
            weaponText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 160);
            dungeonLevelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 190);
            window.draw(interfaceBackground);
            window.draw(playerNameText);
            window.draw(healthText);
            window.draw(strengthText);
            window.draw(defenseText);
            window.draw(levelText);
            window.draw(weaponText);
            window.draw(dungeonLevelText);
        }
        else {
            // Сдвигаем интерфейс за край экрана
            interfaceBackground.setPosition(window.getSize().x, 0);
            playerNameText.setPosition(window.getSize().x + 10, 10);
            healthText.setPosition(window.getSize().x + 10, 40);
            strengthText.setPosition(window.getSize().x + 10, 70);
            defenseText.setPosition(window.getSize().x + 10, 100);
            levelText.setPosition(window.getSize().x + 10, 130);
            weaponText.setPosition(window.getSize().x + 10, 160);
            dungeonLevelText.setPosition(window.getSize().x + 10, 190);
        }
        playerSprite.setPosition(player.getX() * 32, player.getY() * 32);
        window.draw(playerSprite);
        window.display();
    }
    return 0;
}