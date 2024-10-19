#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>

class Enemy {
private:
    std::string name;
    int health;
    int atack;
    bool life;
    int experienceReward;
    sf::RectangleShape shape;
    int x, y;

public:
    // Конструктор
    Enemy(const std::string& enemyName, int hp, int atk, int expReward, int xCoord, int yCoord);

    // Геттеры
    const std::string& getName() const;
    int getHealth() const;
    int getAttack() const;
    bool getLife() const;
    int getExperienceReward() const;
    sf::RectangleShape getShape() const;
    int getX() const;
    int getY() const;

    // Методы
    void takeDamage(int damage);
    void attack(Player& player) const;
    void setPosition(int xCoord, int yCoord);
};

#endif // ENEMY_H
