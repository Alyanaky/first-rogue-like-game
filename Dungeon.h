#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <random>
using namespace std;

class Dungeon {
private:
    int width;
    int height;
    int stairUpX;
    int stairUpY;
    int stairDownX;
    int stairDownY;
    vector<vector<char>> map;

    int random(int min, int max);
    int countLiveNeighbours(int x, int y);
    void generateCellularAutomaton(int iterations);
    void createCorridors();
    void createRoom(int x, int y, int width, int height);
    vector<pair<int, int>> findEmptyAreas();
    void createCorridorBetweenRooms(pair<int, int> room1, pair<int, int> room2);
    void createCorridorsBetweenRooms();
    void createPredefinedCorridors();
    void createPredefinedCorridors2();
    void createPredefinedCorridors4();
    void createPredefinedCorridors5();
    void createPredefinedRooms();

public:
    Dungeon(int w, int h);
    int getWidth();
    int getHeight();
    void setWidth(int a);
    void setHeight(int a);
    int getUpstairX();
    int getUpstairY();
    void generate(int level);
    vector<vector<char>> getMap();
};

#endif // DUNGEON_H
