#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

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
    // Конструктор
    Player(int hp, int str, int def, int exp, int lvl, bool lf, int xCoord, int yCoord);

    // Геттеры
    int getHealth() const;
    int getStrength() const;
    int getExperience() const;
    int getDefense() const;
    int getLevel() const;
    bool getLife() const;
    int getX() const;
    int getY() const;

    // Сеттеры
    void setHealth(int newHealth);
    void setStrength(int newStrength);
    void setExperience(int newExperience);
    void setDefense(int newDefense);
    void setLevel(int newLevel);
    void setLife(bool newLife);
    void setPosition(int xCoord, int yCoord);

    // Методы
    void takeDamage(int damage);
    void move(int dx, int dy, const std::vector<std::vector<char>>& map);
};

#endif // PLAYER_H