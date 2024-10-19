#include "enemy.h"

Enemy::Enemy(const std::string& enemyName, int hp, int atk, int expReward, int xCoord, int yCoord) :
    name(enemyName), health(hp), atack(atk), experienceReward(expReward), x(xCoord), y(yCoord) {
    shape.setSize(sf::Vector2f(32, 32));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x * 32, y * 32);
}

// Геттеры
const std::string& Enemy::getName() const { return name; }
int Enemy::getHealth() const { return health; }
int Enemy::getAttack() const { return atack; }
bool Enemy::getLife() const { return life; }
int Enemy::getExperienceReward() const { return experienceReward; }
sf::RectangleShape Enemy::getShape() const { return shape; }
int Enemy::getX() const { return x; }
int Enemy::getY() const { return y; }

// Методы
void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        life = false;
    }
}

void Enemy::attack(Player& player) const {
    player.takeDamage(atack);
}

void Enemy::setPosition(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
    shape.setPosition(x * 32, y * 32);
}
