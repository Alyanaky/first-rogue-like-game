#include "roguelike.h"
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