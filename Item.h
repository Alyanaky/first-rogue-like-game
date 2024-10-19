#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Player;

class Item {
private:
    string name;
    int damageBonus;
    int defenseBonus;
    int heal;
    int damageToPlayer;
    sf::RectangleShape shape;
    int x, y;

public:
    Item(const string& itemName, int damage = 0, int defense = 0, int HEALcount = 0, int DTP = 0, int xCoord = 0, int yCoord = 0);

    const string& getName() const;
    int getDamageBonus() const;
    int getDefenseBonus() const;
    int getHeal() const;
    int getDamageToPlayer() const;

    void applyEffect(Player& player) const;
    void removeEffect(Player& player) const;
    void setPosition(int xCoord, int yCoord);
};

#endif // ITEM_H
