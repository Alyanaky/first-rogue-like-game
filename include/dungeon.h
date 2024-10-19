#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Dungeon {
private:
    int width;
    int height;
    int stairUpX;
    int stairUpY;
    int stairDownX;
    int stairDownY;
    std::vector<std::vector<char>> map;

    // ��������������� �������
    int random(int min, int max);
    int countLiveNeighbours(int x, int y);
    void generateCellularAutomaton(int iterations);
    void createCorridors();
    void createRoom(int x, int y, int width, int height);
    std::vector<std::pair<int, int>> findEmptyAreas();
    void createCorridorBetweenRooms(std::pair<int, int> room1, std::pair<int, int> room2);
    void createCorridorsBetweenRooms();
    void createPredefinedCorridors();
    void createPredefinedCorridors2();
    void createPredefinedCorridors4();
    void createPredefinedCorridors5();
    void createPredefinedRooms();

public:
    Dungeon(int w, int h);

    // �������
    int getWidth();
    int getHeight();
    int getUpstairX();
    int getUpstairY();

    // �������
    void setWidth(int a);
    void setHeight(int a);

    // ��������� ����������
    void generate(int level);

    // ����� ��� ��������� ����� ����������
    std::vector<std::vector<char>> getMap();
};

#endif // DUNGEON_H
