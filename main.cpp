#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <conio.h>
#include <queue>
#include <ctime>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Dungeon.h"
using namespace std;
using namespace sf;

Item* randomDrop(const vector<Item*>& items) {
    if (items.empty()) {
        return nullptr;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, items.size() - 1);
    int randomIndex = distrib(gen);
    return items[randomIndex];
}

Enemy* randomEnemy(const vector<Enemy*>& enemies) {
    if (enemies.empty()) {
        return nullptr;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, enemies.size() - 1);
    int randomIndex = distrib(gen);
    return enemies[randomIndex];
}

void levelUp(Player& player) {
    if (player.getExperience() >= 100) {
        player.setLevel(2);
        player.setHealth(player.getHealth() + 10);
        player.setStrength(player.getStrength() + 10);
        player.setDefense(player.getDefense() + 2);
    }
    else if (player.getExperience() >= 300) {
        player.setLevel(3);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }
    else if (player.getExperience() >= 400) {
        player.setLevel(4);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }
    else if (player.getExperience() >= 500) {
        player.setLevel(5);
        player.setHealth(player.getHealth() + 15);
        player.setStrength(player.getStrength() + 12);
        player.setDefense(player.getDefense() + 3);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    random_device rd;
    mt19937 gen(rd());

    vector<Item*> items;
    items.push_back(new Item("Sword", 30, 0, 0, 0, 2, 3));
    items.push_back(new Item("Mace", 20, 0, 0, 0, 4, 5));
    items.push_back(new Item("Lancer", 40, 0, 0, 0, 6, 2));
    items.push_back(new Item("Two hand sword", 60, 0, 0, 0, 8, 4));
    items.push_back(new Item("Knife", 15, 0, 0, 0, 10, 1));
    items.push_back(new Item("Axe", 40, 0, 0, 0, 5, 3));
    items.push_back(new Item("Shield", 0, 10, 0, 0, 2, 5));
    items.push_back(new Item("Mail", 0, 40, 0, 0, 4, 2));
    items.push_back(new Item("Leather Mail", 0, 5, 0, 0, 6, 5));
    items.push_back(new Item("Ring mail", 0, 15, 0, 0, 8, 3));
    items.push_back(new Item("Пластинчатая броня", 0, 25, 0, 0, 10, 2));
    items.push_back(new Item("Шлем", 0, 5, 0, 0, 5, 4));
    items.push_back(new Item("Food", 0, 0, 10, 0, 2, 2));
    items.push_back(new Item("Drinking water", 0, 0, 5, 0, 4, 4));
    items.push_back(new Item("Healing potion", 0, 0, 20, 0, 6, 1));
    items.push_back(new Item("Suspicious potion", 0, 0, 0, 30, 8, 2));

    vector<Enemy*> enemies;
    enemies.push_back(new Enemy("Rat", 20, 5, 10, 2, 2));
    enemies.push_back(new Enemy("Spider", 15, 3, 8, 4, 4));
    enemies.push_back(new Enemy("Goblin", 25, 7, 15, 6, 3));
    enemies.push_back(new Enemy("Wolf", 30, 10, 18, 8, 1));
    enemies.push_back(new Enemy("Skeleton", 40, 30, 30, 10, 4));
    enemies.push_back(new Enemy("Zombie", 35, 15, 25, 5, 5));
    enemies.push_back(new Enemy("Undead", 28, 12, 20, 2, 4));
    enemies.push_back(new Enemy("Bandit", 32, 18, 22, 4, 1));
    enemies.push_back(new Enemy("Frenzied wolf", 45, 15, 28, 6, 4));
    enemies.push_back(new Enemy("Zombie", 50, 25, 35, 8, 3));
    enemies.push_back(new Enemy("Ogre", 60, 25, 40, 10, 2));
    enemies.push_back(new Enemy("Troll", 70, 30, 50, 5, 2));
    enemies.push_back(new Enemy("Golem", 80, 40, 60, 2, 5));
    enemies.push_back(new Enemy("Griffin", 55, 28, 45, 4, 3));
    enemies.push_back(new Enemy("Witch", 50, 20, 35, 6, 2));
    enemies.push_back(new Enemy("Werewolf", 65, 35, 55, 8, 4));
    enemies.push_back(new Enemy("Dragon", 100, 50, 80, 10, 3));
    enemies.push_back(new Enemy("Demon", 75, 45, 65, 5, 4));
    enemies.push_back(new Enemy("Ghost", 40, 10, 30, 2, 1));
    enemies.push_back(new Enemy("Ice golem", 120, 60, 100, 4, 2));
    enemies.push_back(new Enemy("Fire demon", 110, 70, 90, 6, 5));
    enemies.push_back(new Enemy("Hydra", 150, 80, 120, 8, 2));
    enemies.push_back(new Enemy("Guardian dragon", 200, 100, 150, 10, 5));
    enemies.push_back(new Enemy("Ancient golem", 180, 90, 130, 5, 3));
    enemies.push_back(new Enemy("Goblin King", 130, 75, 110, 2, 4));
    enemies.push_back(new Enemy("Demon Lord", 160, 95, 140, 4, 5));
    enemies.push_back(new Enemy("Boss", 250, 120, 200, 6, 4));
    enemies.push_back(new Enemy("Final Boss", 400, 150, 250, 8, 3));

    RenderWindow window(VideoMode(50 * 32, 30 * 32), "Game");
    window.setFramerateLimit(60);

    Dungeon dungeon(50, 30);
    dungeon.generate(1);
    int currentLevel = 1;

    Player player(100, 20, 5, 0, 1, true, dungeon.getUpstairX(), dungeon.getUpstairY());

    RectangleShape interfaceBackground(Vector2f(150, window.getSize().y));
    interfaceBackground.setFillColor(Color(0, 0, 0, 150));
    interfaceBackground.setPosition(window.getSize().x - interfaceBackground.getSize().x, 0);

    Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        cout << "Ошибка загрузки шрифта: arial.ttf" << endl;
        return 1;
    }
    Text playerNameText("Name: ", font, 16);
    playerNameText.setFillColor(Color::White);
    playerNameText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 10);

    Text healthText("Health: ", font, 16);
    healthText.setFillColor(Color::White);
    healthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 40);

    Text strengthText("Strenght: ", font, 16);
    strengthText.setFillColor(Color::White);
    strengthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 70);

    Text defenseText("Defense: ", font, 16);
    defenseText.setFillColor(Color::White);
    defenseText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 100);

    Text levelText("Level: ", font, 16);
    levelText.setFillColor(Color::White);
    levelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 130);

    Text weaponText("Weapon: ", font, 16);
    weaponText.setFillColor(Color::White);
    weaponText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 160);

    Text dungeonLevelText("Dungeon Level: 1", font, 16);
    dungeonLevelText.setFillColor(Color::White);
    dungeonLevelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 190);

    bool interfaceVisible = false;

    Texture wallTexture;
    if (!wallTexture.loadFromFile("textures/wall.png")) {
        cout << "Ошибка загрузки изображения: wall.png" << endl;
        return 1;
    }
    Sprite wallSprite(wallTexture);
    wallSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture floorTexture;
    if (!floorTexture.loadFromFile("textures/floor.png")) {
        cout << "Ошибка загрузки изображения: floor.png" << endl;
        return 1;
    }
    Sprite floorSprite(floorTexture);
    floorSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture enemyTexture;
    if (!enemyTexture.loadFromFile("textures/enemy.png")) {
        cout << "Ошибка загрузки изображения: enemy.png" << endl;
        return 1;
    }
    Sprite enemySprite(enemyTexture);
    enemySprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture itemTexture;
    if (!itemTexture.loadFromFile("textures/item.png")) {
        cout << "Ошибка загрузки изображения: item.png" << endl;
        return 1;
    }

    Texture stairUpTexture;
    if (!stairUpTexture.loadFromFile("textures/stairUp.png")) {
        cout << "Ошибка загрузки изображения" << endl;
    }
    Sprite stairUpSprite(stairUpTexture);
    stairUpSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture stairDownTexture;
    if (!stairDownTexture.loadFromFile("textures/stairDown.png")) {
        cout << "Ошибка загрузки изображения" << endl;
    }
    Sprite stairDownSprite(stairDownTexture);
    stairDownSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Sprite itemSprite(itemTexture);
    itemSprite.setTextureRect(IntRect(0, 0, 32, 32));

    Texture playerTexture;
    if (!playerTexture.loadFromFile("textures/player.png")) {
        cout << "Ошибка загрузки спрайта игрока!" << endl;
        return 1;
    }
    Sprite playerSprite(playerTexture);

    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Numpad7) {
                    player.move(-1, -1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad8) {
                    player.move(0, -1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad9) {
                    player.move(1, -1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad4) {
                    player.move(-1, 0, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad6) {
                    player.move(1, 0, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad1) {
                    player.move(-1, 1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad2) {
                    player.move(0, 1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Numpad3) {
                    player.move(1, 1, dungeon.getMap());
                }
                if (event.key.code == Keyboard::Tab) {
                    interfaceVisible = !interfaceVisible;
                }
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
            if (dungeon.getMap()[player.getY()][player.getX()] == 'D') {
                currentLevel++;
                dungeon.generate(currentLevel);
                player.setPosition(dungeon.getUpstairX(), dungeon.getUpstairY());
            }
        }

        window.clear(Color::Black);
        vector<vector<char>> map = dungeon.getMap();
        for (int y = 0; y < dungeon.getHeight(); y++) {
            for (int x = 0; x < dungeon.getWidth(); x++) {
                switch (map[y][x]) {
                case '#':
                    wallSprite.setPosition(x * 32, y * 32);
                    window.draw(wallSprite);
                    break;
                case '.':
                    floorSprite.setPosition(x * 32, y * 32);
                    window.draw(floorSprite);
                    break;
                case 'I':
                    itemSprite.setPosition(x * 32, y * 32);
                    window.draw(itemSprite);
                    break;
                case 'U':
                    floorSprite.setPosition(x * 32, y * 32);
                    window.draw(floorSprite);
                    break;
                case 'D':
                    stairDownSprite.setPosition(x * 32, y * 32);
                    window.draw(stairDownSprite);
                    break;
                }
            }
        }
        window.draw(playerSprite);
        for (int y = 0; y < dungeon.getHeight(); y++) {
            wallSprite.setPosition(0, y * 32);
            window.draw(wallSprite);
            wallSprite.setPosition((dungeon.getWidth() - 1) * 32, y * 32);
            window.draw(wallSprite);
        }
        for (int x = 0; x < dungeon.getWidth(); x++) {
            wallSprite.setPosition(x * 32, 0);
            window.draw(wallSprite);
            wallSprite.setPosition(x * 32, (dungeon.getHeight() - 1) * 32);
            window.draw(wallSprite);
        }
        healthText.setString("Health: " + to_string(player.getHealth()));
        strengthText.setString("Power: " + to_string(player.getStrength()));
        defenseText.setString("Defence: " + to_string(player.getDefense()));
        levelText.setString("Level: " + to_string(player.getLevel()));
        dungeonLevelText.setString("Dungeon Level: " + to_string(currentLevel));
        if (interfaceVisible) {
            interfaceBackground.setPosition(window.getSize().x - interfaceBackground.getSize().x, 0);
            playerNameText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 10);
            healthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 40);
            strengthText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 70);
            defenseText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 100);
            levelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 130);
            weaponText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 160);
            dungeonLevelText.setPosition(window.getSize().x - interfaceBackground.getSize().x + 10, 190);
            window.draw(interfaceBackground);
            window.draw(playerNameText);
            window.draw(healthText);
            window.draw(strengthText);
            window.draw(defenseText);
            window.draw(levelText);
            window.draw(weaponText);
            window.draw(dungeonLevelText);
        }
        else {
            interfaceBackground.setPosition(window.getSize().x, 0);
            playerNameText.setPosition(window.getSize().x + 10, 10);
            healthText.setPosition(window.getSize().x + 10, 40);
            strengthText.setPosition(window.getSize().x + 10, 70);
            defenseText.setPosition(window.getSize().x + 10, 100);
            levelText.setPosition(window.getSize().x + 10, 130);
            weaponText.setPosition(window.getSize().x + 10, 160);
            dungeonLevelText.setPosition(window.getSize().x + 10, 190);
        }
        playerSprite.setPosition(player.getX() * 32, player.getY() * 32);
        window.draw(playerSprite);
        window.display();
    }
    return 0;
}
