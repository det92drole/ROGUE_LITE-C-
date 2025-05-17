#pragma once
#include <SFML/Window.hpp>
#include <iostream>

extern bool moveLeft;
extern bool moveRight;
extern bool moveUp;
extern bool moveDown;
extern float moveSpeed;
extern bool spaceBar;

class KeyManager {
public:
    KeyManager() {
        std::cout<<"listening for keystrokes" << std::endl;
    }
    void update();  // Check for key presses


private:

};
