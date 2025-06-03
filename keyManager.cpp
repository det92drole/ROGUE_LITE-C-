#include "keyManager.h"

bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;
bool spaceBar = false;
float moveSpeed = 500.0f;

KeyManager::KeyManager():escape(false), clickLeft(false), tempLeft(false){
    //std::cout << "listening for keystrokes" << std::endl;
}

void KeyManager::update(sf::Event& event) {

    moveLeft = moveDown = moveUp = moveRight = spaceBar=clickLeft=false;

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

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        escape = true;
        //std::cout << "ESCAPE PRESSED" << std::endl;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            //click press
            tempLeft = true;
            
        }
    }
    if (tempLeft) {
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                //click release
                clickLeft = true;
                tempLeft = false;
            }
        }
    }

    if (saveMenu) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {
                if (!input.empty())
                    input.pop_back();
            }
            else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                input += static_cast<char>(event.text.unicode);
            }
        }
    }
}
    
