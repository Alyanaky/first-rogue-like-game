#include "roguelike.h"
class Dungeon {
private:
    int width;
    int height;
    vector<vector<char>> map;

    // Генерация случайного числа в заданном диапазоне
    int random(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);
        return distrib(gen);
    }

    // Генерация комнат
    void generateRooms(int numRooms) {
        for (int i = 0; i < numRooms; ++i) {
            // Случайные размеры комнаты
            int roomWidth = random(4, 10);
            int roomHeight = random(4, 10);

            // Случайные координаты комнаты
            int roomX = random(1, width - roomWidth);
            int roomY = random(1, height - roomHeight);

            // Проверка, не пересекается ли комната с другими комнатами
            bool intersects = false;
            for (int y = roomY; y < roomY + roomHeight; ++y) {
                for (int x = roomX; x < roomX + roomWidth; ++x) {
                    if (map[y][x] != '#') {
                        intersects = true;
                        break;
                    }
                }
                if (intersects) {
                    break;
                }
            }

            // Если комната не пересекается, то создаем её
            if (!intersects) {
                for (int y = roomY; y < roomY + roomHeight; ++y) {
                    for (int x = roomX; x < roomX + roomWidth; ++x) {
                        map[y][x] = '.';
                    }
                }
            }
            else {
                // Если комната пересекается, то генерируем её заново
                --i;
            }
        }
    }

    // Создание коридора между двумя комнатами
    void createCorridor(int x1, int y1, int x2, int y2) {
        // Выбираем случайный путь: горизонтальный или вертикальный
        bool horizontal = random(0, 1);

        // Горизонтальный коридор
        if (horizontal) {
            for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
                map[y1][x] = '.';
            }
            for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
                map[y][x2] = '.';
            }
        }
        else {
            // Вертикальный коридор
            for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
                map[y][x1] = '.';
            }
            for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
                map[y2][x] = '.';
            }
        }
    }

    // Соединение комнат коридорами
    void connectRooms() {
        // Находим центры комнат
        vector<pair<int, int>> roomCenters;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (map[y][x] == '.') {
                    // Проверяем, не является ли текущая клетка центром комнаты
                    bool isRoomCenter = true;
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dx = -1; dx <= 1; ++dx) {
                            if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
                                if (map[y + dy][x + dx] == '#') {
                                    isRoomCenter = false;
                                    break;
                                }
                            }
                        }
                        if (!isRoomCenter) {
                            break;
                        }
                    }
                    if (isRoomCenter) {
                        roomCenters.push_back({ x, y });
                    }
                }
            }
        }

        // Соединяем комнаты попарно
        for (int i = 0; i < roomCenters.size() - 1; ++i) {
            createCorridor(roomCenters[i].first, roomCenters[i].second, roomCenters[i + 1].first, roomCenters[i + 1].second);
        }
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

    // Сеттеры
    void setWidth(int a) {
        width = a;
    }
    void setHeight(int a) {
        height = a;
    }

    // Генерация подземелья
    void generate() {
        // Генерация комнат
        generateRooms(random(4, 8));

        // Соединение комнат
        connectRooms();

    }
    // Метод для получения карты подземелья
    vector<vector<char>> getMap() {
        return map;
    }
};