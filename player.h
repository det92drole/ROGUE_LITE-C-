#pragma once
#include <SFML/Graphics.hpp>
#include "render.h"
#include "keyManager.h"
#include <optional>

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
    int spellType;

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
    std::optional<FireBall> createFireBall(float spawnX, float spawnY, int spell);
    Item createKey(float x,float y);
    int getHealth() const;
    void setHealth(int health);
    float getMana() { return playerMana; }
    void setMana(float val) { playerMana = val; }
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
    int getKeyCount() { return keyCount; }
    void setKeyCount(int val) { keyCount = val; }
    sf::Texture& getRedFireTexture() { return tF; }
    sf::Texture& getBlueFireTexture() { return tBlue; }

    int getSpell() { return equipedSpell; }
    void setSpell(int val) { equipedSpell = val; }
    void setFlashTimer(float val) { hitFlashTimer = val; }
    float getFlashTimer() { return hitFlashTimer; }
    bool getIsMoving() { return isMoving; }
    bool getIsHit() { return isHit; }
    void setIsHit(bool val) { isHit = val; }

private:

    sf::Texture tD; //texture down move
    sf::Texture tR; //texture right move
    sf::Texture tL; //texture left move
    sf::Texture tU; //texture up move
    sf::Texture tF; //fireball texture
    sf::Texture tBlue; //blue spell texture

    sf::Texture tKey;

    sf::Sprite sprite;

    int frame;
    float frameTime;
    float elapsedTime;
    float hitFlashTimer;
    float playerPosX, playerPosY;
    float prevX, prevY;
    int playerHealth;
    float playerMana;
    int direction;
    bool canMove;
    bool isMoving;
    bool isHit;
    int keyCount;
    int equipedSpell;
    static std::vector<Player> playerArr;
    std::vector<FireBall> fireBalls;
    std::vector<Item> keys;

};