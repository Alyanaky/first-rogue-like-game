#include "roguelike.h"
// Класс предмета
class Item {
private:
    string name; // Название предмета
    int damageBonus; // Бонус к урону, который дает предмет (может быть отрицательным для брони)
    int defenseBonus; // Бонус к защите, который дает предмет (может быть отрицательным для оружия)
    int heal;
    int damageToPlayer;
    RectangleShape shape; // Форма предмета для отрисовки
    int x, y; // Координаты предмета
public:
    // Конструктор
    Item(const string& itemName, int damage = 0, int defense = 0, int HEALcount = 0, int DTP = 0, int xCoord = 0, int yCoord = 0) :
        name(itemName), damageBonus(damage), defenseBonus(defense), heal(HEALcount), damageToPlayer(DTP), x(xCoord), y(yCoord) {
        shape.setSize(Vector2f(32, 32)); // Размер формы предмета
        shape.setFillColor(Color::Green); // Цвет формы предмета
        shape.setPosition(x * 32, y * 32); // Позиция формы предмета
    }

    // Геттеры для получения информации о предмете
    const string& getName() const { return name; }

    int getDamageBonus() const { return damageBonus; }
    int getDefenseBonus() const { return defenseBonus; }
    int getHeal() const { return heal; }
    int getDamageToPlayer() const { return damageToPlayer; }
    RectangleShape getShape() const { return shape; }
    int getX() const { return x; }
    int getY() const { return y; }

    // Метод для применения эффекта предмета к игроку
    void applyEffect(Player& player) const {
        player.setStrength(player.getStrength() + damageBonus);
        player.setDefense(player.getDefense() + defenseBonus);
        player.setHealth(player.getHealth() + heal);
    }

    // Метод для удаления эффекта предмета от игрока
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