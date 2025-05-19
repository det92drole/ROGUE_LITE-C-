#include "gameState.h"

void GameManager::drawMenu(sf::RenderWindow& window, Player& player, GameState gameState) {
    //std::cout << "DRAW MENU CALLE1" << std::endl;
    if (gameState == GameState::Paused) {
        //std::cout << "DRAW MENU CALLE2" << std::endl;

        sf::Vector2f size(window.getSize().x / 2.0f, window.getSize().y - window.getSize().y / 4.0f);

        // Convert screen-space size to world scale by applying the view's scaling
        sf::View view = window.getView();
        float scaleX = view.getSize().x / window.getSize().x;
        float scaleY = view.getSize().y / window.getSize().y;

        sf::Vector2f worldSize(size.x * scaleX, size.y * scaleY);

        // Center the menu around the player's world position
        sf::Vector2f position(player.getPosX()*100 - worldSize.x / 2.0f, player.getPosY()*100 - worldSize.y / 2.0f);

        sf::RectangleShape border;
        border.setSize(worldSize);
        border.setPosition(position);
        border.setFillColor(sf::Color(255, 0, 0, 100)); // red
        border.setOutlineColor(sf::Color::Red);
        border.setOutlineThickness(3.0f);

        window.draw(border);

    }
    
}

void GameManager::drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState gameState) {
    renderer.drawGrid();
    player.draw(window);
    enemy.draw(window);
    drawMenu(window, player, gameState);

}

void GameManager::gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
    bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer) {
    //std::cout << keyManager.getEsc() << std::endl;
    if (gameState == GameState::Playing) {
        // update game world (movement, collisions, etc.)
        if (keyManager.getEsc()) {
            gameState = GameState::Paused;
            std::cout << "GAME PAUSED"<<std::endl;
            keyManager.setEsc(false);
        }
        else {
            player.update(deltaTime, left, right, up, down, space);
            collisions(player, exitX, exitY, player.getDirection(), enemy, deltaTime);
            enemy.update(deltaTime);

        }
        drawGame(window, player, enemy, renderer, gameState);

    }
    else if (gameState == GameState::Paused) {
        // skip updates, or run menu animations
        //std::cout << "GAME STILL PAUSED" << std::endl;
        if (keyManager.getEsc()) {
            gameState = GameState::Playing;
            std::cout << "GAME UNPAUSED"<<std::endl;
            keyManager.setEsc(false);
        }
        drawGame(window, player, enemy, renderer, gameState);

    }
}