#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
using namespace std;

class Player {
private:
    int health;
    int strength;
    int experience;
    int defense;
    int level;
    bool life;
    int x, y;

public:
    Player(int hp, int str, int def, int exp, int lvl, bool lf, int xCoord, int yCoord);

    int getHealth() const;
    int getStrength() const;
    int getExperience() const;
    int getDefense() const;
    int getLevel() const;
    bool getLife() const;
    int getX() const;
    int getY() const;

    void setHealth(int newHealth);
    void setStrength(int newStrength);
    void setExperience(int newExperience);
    void setDefense(int newDefense);
    void setLevel(int newLevel);
    void setLife(bool newLife);
    void setPosition(int xCoord, int yCoord);

    void takeDamage(int damage);
    void move(int dx, int dy, const vector<vector<char>>& map);
};

#endif // PLAYER_H
