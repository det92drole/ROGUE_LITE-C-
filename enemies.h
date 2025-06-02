#pragma once
#include <SFML/Graphics.hpp>
#include "render.h"
#include "rand.h"
#include "debug.h"
#include <bitset>
#include <memory>

class Renderer;

class Enemy {
public:
    Enemy();

    int getHealth() const;
    void setHealth(int health);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    void changeXY(float x, float y);
    float getPosX() const { return enemyPosX; }
    float getPosY() const { return enemyPosY; }
    void spawnEnemies();
    static std::vector<Enemy>& getEnemies(); 
    int getDirection() { return direction; }
    float getSpeed() { return speed; }
    void setPosX(float x) { enemyPosX = x; }
    void setPosY(float y) { enemyPosY = y; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setDirection(int d) { direction = d; }
    int getWidthPx() const { return widthPx; }
    int getHeightPx() const { return heightPx; }
    void setWidthPx(int val) { widthPx=val; }
    void setHeightPx(int val) { heightPx = val; }
    float getEpsilon() { return epsilon; }
    void setAgro(bool val) { agro = val; }
    bool getAgro() { return agro; }
    int getID() { return id; }
    void setID(int val) { id = val; }
    void setFrame(int val) { frame = val; }
    int getFrame() { return frame; }
    void setTextSelect(int val) { textSelect = val; }
    int getTextSelect() { return textSelect; }
    static std::vector<std::shared_ptr<sf::Texture>>& getTextures();
    sf::Sprite& getSprite() { return sprite; }


private:

    static std::vector<std::shared_ptr<sf::Texture>> textures;  
    sf::Sprite sprite;

    int id;
    int frame;
    float frameTime;
    float elapsedTime;
    float enemyPosX, enemyPosY;
    int enemyHealth;
    int direction;
    float speed;
    float epsilon;
    int widthPx;
    int heightPx;
    bool agro;
    int textSelect;

    //static std::vector<Enemy> enemyArr;

};