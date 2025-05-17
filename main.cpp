#include <iostream>
#include <SFML/Graphics.hpp>
#include "rand.h"
#include "windowManager.h"
#include "render.h"
#include "keyManager.h"
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"
#include "debug.h"

int main() {
    std::srand(std::time(0));  // seed rand with time stamp
    sf::Clock clock;

    KeyManager keyManager;  // 

    popGrid();
    //printGrid();

    Player player; //created AFTER grid and spawn determined by printGrid();
    Enemy enemy;

    enemy.spawnEnemies();

    
    sf::Color backgroundColor(58, 9, 235);
    WindowManager windowManager(800, 600, "MAP&GAME");
    sf::RenderWindow& window = windowManager.getWindow();
    Renderer renderer(windowManager); // Pass windowManager to Renderer
    window.setFramerateLimit(60);
   
    while (window.isOpen())
    {
        windowManager.processEvents();
        sf::Time dt = clock.restart();

        keyManager.update();  // Check for key presses
        player.update(dt, moveLeft, moveRight, moveUp, moveDown, spaceBar);
        collisions(player, exitX, exitY, player.getDirection(), enemy, dt);
        enemy.update(dt);

        //draw here
        window.clear(backgroundColor);
        renderer.drawGrid(); 
        player.draw(window);
        enemy.draw(window);

        windowManager.playerView(player.getPosX(), player.getPosY(), squareSize); //camera centered on player
        window.display();
    }
    
    
    return 0;

}