#pragma once
#include <SFML/Graphics.hpp>
#include "render.h"
#include "keyManager.h"

class Renderer;

struct FireBall {
    sf::Sprite spriteBall;
    float x;
    float y;
    float speed = 0.0f;
    float epsilon = 0.1f;
    bool FLeft = false;
    bool FRight = false;
    bool FUp = false;
    bool FDown = false;
    int direction;
    float widthPx;
    float heightPx;

    int frame = 0;
    float elapsedTime = 0.0f;

    float getX() { return x; }
    float getY() { return y; }
    void setX(float val) { x = val; }
    void setY(float val) { y = val; }
    float getEpsilon() { return epsilon; }
    float getSpeed() { return speed; }
    float getWidth() { return widthPx; }
    float getHeight() { return heightPx; }
};

struct Item {
    sf::Sprite itemSprite;
    float x, y;
    float widthPx, heightPx;
    float getX() { return x; }
    float getY() { return y; }
    void setX(float val) { x = val; }
    void setY(float val) { y = val; }
};

class Player {
public:
    Player(); // Constructor
    FireBall createFireBall(float spawnX, float spawnY);
    Item createKey(float x,float y);
    int getHealth() const;
    void setHealth(int health);
    void update(sf::Time deltaTime, bool left, bool right, bool up, bool down, bool space);
    void draw(sf::RenderWindow& window);
    void changeXY(float x, float y);

    float getPosX() const { return playerPosX; }
    void setPosX(float x) { playerPosX = x; }
    void setPosY(float y) { playerPosY = y; }
    float getPosY() const { return playerPosY; }
    int getDirection() const { return direction; }
    void setDirection(int dir) { direction = dir; }
    void setCanMove(bool v) { canMove = v; }
    bool getMoveBool() { return canMove; }
    sf::Sprite& getSprite() { return sprite; }
    static std::vector<Player>& getPlayers();
    void testArrPlayer();
    std::vector<FireBall>& getFireBalls() {
        return fireBalls;
    }
    std::vector<Item>& getKeys() {
        return keys;
    }
    bool loadTextures();

private:

    sf::Texture tD; //texture down move
    sf::Texture tR; //texture right move
    sf::Texture tL; //texture left move
    sf::Texture tU; //texture up move
    sf::Texture tF; //fireball texture
    sf::Texture tKey;

    sf::Sprite sprite;

    int frame;
    float frameTime;
    float elapsedTime;
    float playerPosX, playerPosY;
    int playerHealth;
    int direction;
    bool canMove;
    static std::vector<Player> playerArr;
    std::vector<FireBall> fireBalls;
    std::vector<Item> keys;

};