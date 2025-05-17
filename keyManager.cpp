#include "keyManager.h"

bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;
bool spaceBar = false;
float moveSpeed = 500.0f;

void KeyManager::update() {

    moveLeft = moveDown = moveUp = moveRight = spaceBar = false;

    // Check for key presses and update windowManager viewPort
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        //
        moveUp = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //
        moveLeft = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //
        moveDown = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //
        moveRight = true;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //
        spaceBar = true;
    }
}