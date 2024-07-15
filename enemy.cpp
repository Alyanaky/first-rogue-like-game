#include "roguelike.h"
// ����� �����
class Enemy {
private:
    string name; // ��� �����
    int health; // �������� �����
    int atack; // ����, ������� ���� ������� ������
    bool life = true;
    int experienceReward; // ���������� �����, ������� ����� �������� �� ������ ��� ������
    RectangleShape shape; // ����� ����� ��� ���������
    int x, y; // ���������� �����
public:
    // �����������
    Enemy(const string& enemyName, int hp, int atk, int expReward, int xCoord, int yCoord) :
        name(enemyName), health(hp), atack(atk), experienceReward(expReward), x(xCoord), y(yCoord) {
        shape.setSize(Vector2f(32, 32)); // ������ ����� �����
        shape.setFillColor(Color::Red); // ���� ����� �����
        shape.setPosition(x * 32, y * 32); // ������� ����� �����
    }

    // ������� ��� ��������� ���������� � �����
    const string& getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return atack; }
    bool getLife() const { return life; }
    int getExperienceReward() const { return experienceReward; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // ����� ��� ��������� ����� ������
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            life = false;
        }
    }

    // ����� ��� ��������� ����� ������ ������
    void attack(Player& player) const {
        player.takeDamage(atack);
    }

    void setPosition(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
        shape.setPosition(x * 32, y * 32);
    }
};