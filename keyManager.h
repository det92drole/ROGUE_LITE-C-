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
    KeyManager();
    void update(sf::Event& event);  // Check for key presses
    bool getEsc() { return escape; }
    void setEsc(bool val) { escape = val; }
private:
    bool escape;
};
