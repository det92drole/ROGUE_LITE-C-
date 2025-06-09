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
    int getDirection() { return direction; }
    float getSpeed() { return speed; }
    void setPosX(float x) { enemyPosX = x; }
    void setPosY(float y) { enemyPosY = y; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setDirection(int d) { direction = d; }
    int getWidthPx() const { return widthPx; }
    int getHeightPx() const { return heightPx; }
    void setWidthPx(int val) { widthPx = val; }
    void setHeightPx(int val) { heightPx = val; }
    float getEpsilon() { return epsilon; }
    void setAgro(bool val) { agro = val; }
    bool getAgro() { return agro; }
    int getID() { return id; }
    void setID(int val) { id = val; }
    void setFrame(int val) { frame = val; }
    int getFrame() { return frame; }

    void spawnEnemies();
    static std::vector<Enemy>& getEnemies();
    void setTextSelect(int val) { textSelect = val; }
    int getTextSelect() { return textSelect; }
    static std::vector<std::shared_ptr<sf::Texture>>& getTextures();
    sf::Sprite& getSprite() { return sprite; }

    void bossSpawn(int exitX, int exitY);
    static std::vector<Enemy>& getBoss();
    void setBossTexture(int val) { bossTextSelect = val; }
    int getBossTexture() { return bossTextSelect; }
    static std::vector<std::shared_ptr<sf::Texture>>& getBossTextures(); 

private:
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
    sf::Sprite sprite;


    static std::vector<std::shared_ptr<sf::Texture>> textures;
    int textSelect;

    static std::vector<std::shared_ptr<sf::Texture>> texturesBoss;
    int bossTextSelect;
};