#include "player.h"

Player::Player(int hp, int str, int def, int exp, int lvl, bool lf, int xCoord, int yCoord) :
    health(hp), strength(str), defense(def), experience(exp), level(lvl), life(lf), x(xCoord), y(yCoord) {}

// Геттеры
int Player::getHealth() const { return health; }
int Player::getStrength() const { return strength; }
int Player::getExperience() const { return experience; }
int Player::getDefense() const { return defense; }
int Player::getLevel() const { return level; }
bool Player::getLife() const { return life; }
int Player::getX() const { return x; }
int Player::getY() const { return y; }

// Сеттеры
void Player::setHealth(int newHealth) { health = newHealth; }
void Player::setStrength(int newStrength) { strength = newStrength; }
void Player::setExperience(int newExperience) { experience = newExperience; }
void Player::setDefense(int newDefense) { defense = newDefense; }
void Player::setLevel(int newLevel) { level = newLevel; }
void Player::setLife(bool newLife) { life = newLife; }
void Player::setPosition(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
}

// Методы
void Player::takeDamage(int damage) {
    health -= (damage - defense);
    if (health <= 0) {
        life = false;
    }
}

void Player::move(int dx, int dy, const std::vector<std::vector<char>>& map) {
    if (x + dx < 1 || x + dx >= map[0].size() ||
        y + dy < 1 || y + dy >= map.size() ||
        map[y + dy][x + dx] == '#') {
        return;
    }
    x += dx;
    y += dy;
}
