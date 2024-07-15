#include "roguelike.h"
// ����� ��������
class Item {
private:
    string name; // �������� ��������
    int damageBonus; // ����� � �����, ������� ���� ������� (����� ���� ������������� ��� �����)
    int defenseBonus; // ����� � ������, ������� ���� ������� (����� ���� ������������� ��� ������)
    int heal;
    int damageToPlayer;
    RectangleShape shape; // ����� �������� ��� ���������
    int x, y; // ���������� ��������
public:
    // �����������
    Item(const string& itemName, int damage = 0, int defense = 0, int HEALcount = 0, int DTP = 0, int xCoord = 0, int yCoord = 0) :
        name(itemName), damageBonus(damage), defenseBonus(defense), heal(HEALcount), damageToPlayer(DTP), x(xCoord), y(yCoord) {
        shape.setSize(Vector2f(32, 32)); // ������ ����� ��������
        shape.setFillColor(Color::Green); // ���� ����� ��������
        shape.setPosition(x * 32, y * 32); // ������� ����� ��������
    }

    // ������� ��� ��������� ���������� � ��������
    const string& getName() const { return name; }

    int getDamageBonus() const { return damageBonus; }
    int getDefenseBonus() const { return defenseBonus; }
    int getHeal() const { return heal; }
    int getDamageToPlayer() const { return damageToPlayer; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // ����� ��� ���������� ������� �������� � ������
    void applyEffect(Player& player) const {
        player.setStrength(player.getStrength() + damageBonus);
        player.setDefense(player.getDefense() + defenseBonus);
        player.setHealth(player.getHealth() + heal);
    }

    // ����� ��� �������� ������� �������� �� ������
    void removeEffect(Player& player) const {
        player.setStrength(player.getStrength() - damageBonus);
        player.setDefense(player.getDefense() - defenseBonus);
    }

    void setPosition(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
        shape.setPosition(x * 32, y * 32);
    }
};