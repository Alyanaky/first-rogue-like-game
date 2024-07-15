#include "roguelike.h"
// ����� ������
class Player {
private:
    int health;  // �������� ������
    int strength; // ���� ������, �������� �� ����
    int experience; // ���� ������, ������������� ��� ������ ��� �������
    int defense;  // ������ ������, ������� ���������� ����
    int level; // �������
    bool life;
    RectangleShape shape; // ����� ������ ��� ���������
    int x, y; // ���������� ������
public:
    // �����������: �������������� �������������� ��� �������� ������� Player
    Player(int hp, int str, int def, int exp, int lvl, bool lf, int xCoord, int yCoord) :
        health(hp), strength(str), defense(def), experience(exp), level(lvl), life(lf), x(xCoord), y(yCoord) {}

    // ������ "getter" (��������� ��������): ���������� ������� �������� ��������������
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    int getExperience() const { return experience; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    bool getLife() const { return life; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // ������ "setter" (��������� ��������): �������� �������� ��������������
    void setHealth(int newHealth) { health = newHealth; }
    void setStrength(int newStrength) { strength = newStrength; }
    void setExperience(int newExperience) { experience = newExperience; }
    void setDefense(int newDefense) { defense = newDefense; }
    void setLevel(int newLevel) { level = newLevel; }
    void setLife(bool newLife) { life = newLife; }
    void setPosition(int xCoord, int yCoord) {
    }

    // ����� ��� ��������� �����
    void takeDamage(int damage) {
        health -= (damage - defense);  // ��������� ������ ��� ��������� �����
        if (health <= 0) {
            life = false;
            // ����� ����� �������� ������ ��������� ����
        }
    }
};