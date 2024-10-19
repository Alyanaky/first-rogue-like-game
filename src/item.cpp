#include "item.h"

Item::Item(const std::string& itemName, int damage, int defense, int HEALcount, int DTP, int xCoord, int yCoord) :
    name(itemName), damageBonus(damage), defenseBonus(defense), heal(HEALcount), damageToPlayer(DTP) {
    shape.setSize(sf::Vector2f(32, 32));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(xCoord * 32, yCoord * 32);
}

// Геттеры
const std::string& Item::getName() const { return name; }
int Item::getDamageBonus() const { return damageBonus; }
int Item::getDefenseBonus() const { return defenseBonus; }
int Item::getHeal() const { return heal; }
int Item::getDamageToPlayer() const { return damageToPlayer; }

// Методы
void Item::applyEffect(Player& player) const {
    player.setStrength(player.getStrength() + damageBonus);
    player.setDefense(player.getDefense() + defenseBonus);
    player.setHealth(player.getHealth() + heal);
}

void Item::removeEffect(Player& player) const {
    player.setStrength(player.getStrength() - damageBonus);
    player.setDefense(player.getDefense() - defenseBonus);
}

void Item::setPosition(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
    shape.setPosition(x * 32, y * 32);
}
