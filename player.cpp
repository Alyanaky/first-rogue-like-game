#include "roguelike.h"
// Класс игрока
class Player {
private:
    int health;  // Здоровье игрока
    int strength; // Сила игрока, влияющая на урон
    int experience; // Опыт игрока, накапливается при победе над врагами
    int defense;  // Защита игрока, снижает получаемый урон
    int level; // Уровень
    bool life;
    RectangleShape shape; // Форма игрока для отрисовки
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
    RectangleShape getShape() const { return shape; }
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
};