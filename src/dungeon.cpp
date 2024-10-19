#include "dungeon.h"

#include <random>
#include <iostream>

Dungeon::Dungeon(int w, int h) : width(w), height(h) {
    map.resize(height, std::vector<char>(width, '#'));
}

// �������
int Dungeon::getWidth() { return width; }
int Dungeon::getHeight() { return height; }
int Dungeon::getUpstairX() { return stairUpX; }
int Dungeon::getUpstairY() { return stairUpY; }

// �������
void Dungeon::setWidth(int a) { width = a; }
void Dungeon::setHeight(int a) { height = a; }

// ��������� ���������� ����� � �������� ���������
int Dungeon::random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// ������� ����� ������� ��� ������
int Dungeon::countLiveNeighbours(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            if (x + dx >= 0 && x + dx < width &&
                y + dy >= 0 && y + dy < height &&
                map[y + dy][x + dx] == '#') {
                count++;
            }
        }
    }
    return count;
}

// �������� ���������� ��������
void Dungeon::generateCellularAutomaton(int iterations) {
    // ��������� ����� ���������� �������� (�����/���)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (random(0, 100) < 60) {
                map[y][x] = '#';
            }
            else {
                map[y][x] = '.';
            }
        }
    }

    // �������� ���������� ��������
    for (int i = 0; i < iterations; ++i) {
        std::vector<std::vector<char>> tempMap = map;

        // ���������� �� ������ ������
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                // ������� ����� �������
                int liveNeighbours = countLiveNeighbours(x, y);

                // ��������� ������� ���������� ��������
                if (map[y][x] == '#' && (liveNeighbours < 2 || liveNeighbours > 5)) {
                    tempMap[y][x] = '.';
                }
                else if (map[y][x] == '.' && liveNeighbours == 3) {
                    tempMap[y][x] = '#';
                }
            }
        }

        // ��������� �����
        map = tempMap;
    }
}

// �������� ���������
void Dungeon::createCorridors() {
    // ���������� �� �����, ���� ����� ��� ���������
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            if (map[y][x] == '.' &&
                (map[y - 1][x] == '#' || map[y + 1][x] == '#' ||
                    map[y][x - 1] == '#' || map[y][x + 1] == '#')) {
                // ������� ����� �����/������
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

// ������� ��� �������� ������� � �������� �����������
void Dungeon::createRoom(int x, int y, int width, int height) {
    for (int row = y; row < y + height; ++row) {
        for (int col = x; col < x + width; ++col) {
            if (row >= 0 && row < height && col >= 0 && col < width) {
                map[row][col] = '.';
            }
        }
    }
}

// ������� ��� ������ ������ ��������
std::vector<std::pair<int, int>> Dungeon::findEmptyAreas() {
    std::vector<std::pair<int, int>> emptyAreas;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == '.') {
                // ���������, ��� ������ �� �������� � ������ ������ ��������
                if (x > 0 && map[y][x - 1] == '#' &&
                    x < width - 1 && map[y][x + 1] == '#' &&
                    y > 0 && map[y - 1][x] == '#' &&
                    y < height - 1 && map[y + 1][x] == '#') {
                    emptyAreas.push_back(std::make_pair(x, y));
                }
            }
        }
    }
    return emptyAreas;
}

// �������� �������� ����� ����� ���������
void Dungeon::createCorridorBetweenRooms(std::pair<int, int> room1, std::pair<int, int> room2) {
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

// �������� ��������� ����� ���������
void Dungeon::createCorridorsBetweenRooms() {
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

// ������� �������� ����� ��������� (��������������)
void Dungeon::createPredefinedCorridors() {
    for (int y = 0; y < height; y += 2) {
        for (int x = 0; x < width; x++) {
            if (x % 10 == 0 && map[y][x] == '#' && map[y][x + 1] == '#') {
                map[y][x] = '.';
                map[y][x + 1] = '.';
                x += 2;
            }
        }
    }
}

// ������� �������� ����� ��������� (������������)
void Dungeon::createPredefinedCorridors2() {
    int r = random(1, height);
    for (int x = 0; x < width; x++) {
        map[r][x] = '.';
    }
}

// ������� �������� ����� ��������� (������������)
void Dungeon::createPredefinedCorridors4() {
    int r = random(1, width);
    int r2 = random(3, 15);
    for (int x = 0; x < height; x++) {
        map[x][r] = '.';
    }
    map[r2][r] = 'D';
    stairDownX = r;
    stairDownY = r2;
}

// ������� �������� ����� ��������� (������������)
void Dungeon::createPredefinedCorridors5() {
    int r = random(1, width);
    int r2 = random(3, 12);
    for (int x = 0; x < height; x++) {
        map[x][r] = '.';
    }
    map[8][r] = 'U';
    stairUpX = r;
    stairUpY = r2;
}


// ������� ������� (������ ��������������)
void Dungeon::createPredefinedRooms() {
    createRoom(2, 2, 10, 12);
    createRoom(width / 2 - 3, height / 2 - 3, 10, 10);
    createRoom(width - 6, height - 6, 12, 13);
}


// ��������� ����������
void Dungeon::generate(int level) {
    // ���������� ��������� ������� ��� ������� ���������
    generateCellularAutomaton(10);
    createPredefinedRooms();
    createPredefinedCorridors();
    createPredefinedCorridors2();
    createPredefinedCorridors2();
    createPredefinedCorridors4();
    createPredefinedCorridors5();
    createPredefinedCorridors5();
    createCorridorsBetweenRooms();
    // ��������� ��������� ��������
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == '.') {
                if (random(1, 75) == 5) {
                    map[y][x] = 'I';
                }
            }
        }
    }
}
// ����� ��� ��������� ����� ����������
std::vector<std::vector<char>> Dungeon::getMap() { return map; }