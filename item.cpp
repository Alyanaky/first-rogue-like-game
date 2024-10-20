#include "Item.h"
#include "Player.h"

Item::Item(const string& itemName, int damage, int defense, int HEALcount, int DTP, int xCoord, int yCoord)
    : name(itemName), damageBonus(damage), defenseBonus(defense), heal(HEALcount), damageToPlayer(DTP), x(xCoord), y(yCoord) {
    shape.setSize(sf::Vector2f(32, 32));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x * 32, y * 32);
}

const string& Item::getName() const { return name; }
int Item::getDamageBonus() const { return damageBonus; }
int Item::getDefenseBonus() const { return defenseBonus; }
int Item::getHeal() const { return heal; }
int Item::getDamageToPlayer() const { return damageToPlayer; }

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
