#pragma once
#include "windowManager.h"
#include "rand.h"

extern std::vector<sf::Sprite> spritesM;
extern float scaleX;
extern int squareSize;

class Renderer {
public:
    Renderer(WindowManager& wm); // Constructor takes WindowManager reference
    void drawGrid();

private:
    WindowManager& windowManager;
    //Player& player;

};
