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
#include "gameState.h"

int main() {

    //----REFERENCE & INPUT-----
    std::srand(std::time(0));  // seed rand with time stamp
    sf::Clock clock;
    KeyManager keyManager;
    //popGrid();
    //printGrid();
    
    //-----GAME ENTITIES-----
    Player player; //created AFTER grid and spawn determined by printGrid();
    Enemy enemy;
    //player.getKeys().emplace_back(player.createKey(keyX, keyY));
    //enemy.spawnEnemies();

    //-----OBSERVER-----
    sf::Color backgroundColor(58, 9, 235);
    WindowManager windowManager(800, 600, "MAP&GAME");
    sf::RenderWindow& window = windowManager.getWindow();
    Renderer renderer(windowManager); // Pass windowManager to Renderer
    window.setFramerateLimit(60);

    //-----MENU-----
    GameManager game(window, player);

    while (window.isOpen())
    {
        //-----GAME AXIOMS-----
        sf::Time dt = clock.restart();
        windowManager.processEvents(keyManager); //key manager called here

        //-----REFRESH & REFERENCE-----
        window.clear(backgroundColor);
        windowManager.playerView(player.getPosX(), player.getPosY(), squareSize); //camera centered on player

        //-----GAME MECH & DRAW-----
        game.gameCheck(player, exitX, exitY, player.getDirection(), enemy, dt, 
            moveLeft, moveRight, moveUp, moveDown, spaceBar, keyManager, window, renderer); //game update and draw mech

        //-----OUTPUT-----
        window.display();

    }
    return 0;
}