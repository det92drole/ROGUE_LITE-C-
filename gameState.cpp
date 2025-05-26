#include "gameState.h"



GameManager::GameManager(sf::RenderWindow& window, Player& player) :gameState(GameState::Playing) {
    if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    //spawnBtn(window, player, gameState);
    
}

void GameManager::spawnBtn(sf::RenderWindow& window, Player& player, GameState& gameState) {

    //ON BACK BURNER

    sf::Vector2f size(window.getSize().x / 2.0f, window.getSize().y - window.getSize().y / 4.0f);

    // Convert screen-space size to world scale by applying the view's scaling
    sf::View view = window.getView();
    float scaleX = view.getSize().x / window.getSize().x;
    float scaleY = view.getSize().y / window.getSize().y;

    sf::Vector2f worldSize(size.x * scaleX, size.y * scaleY);
    sf::Vector2f positionMenu(player.getPosX() * 100 - worldSize.x / 2.0f, player.getPosY() * 100 - worldSize.y / 2.0f);

    //currently two non-equipment buttons

    Button newBtn;
    newBtn.x;
    newBtn.y;
    newBtn.height;
    newBtn.width;
    //return newBtn;

    buttons[newBtn.stringText] = newBtn;
    
    
}

void GameManager::drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState) {
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
        sf::Vector2f positionMenu(player.getPosX()*100 - worldSize.x / 2.0f, player.getPosY()*100 - worldSize.y / 2.0f);

        sf::RectangleShape border;
        border.setSize(worldSize);
        border.setPosition(positionMenu);
        border.setFillColor(sf::Color(255, 0, 0, 100)); // red
        border.setOutlineColor(sf::Color::Red);
        border.setOutlineThickness(3.0f);

        window.draw(border);

        // ---- TEXT ----
        sf::Text title;
        title.setFont(font); // must be accessible from this scope
        title.setString("Game Paused");
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::White);
        title.setPosition(positionMenu.x + 20, positionMenu.y + 20);
        window.draw(title);

        // ---- BUTTON: Resume ----
        float width = 150.f;
        float height = 40.f;
        resumeBtn.setSize(sf::Vector2f(width, height));
        resumeBtn.setPosition(positionMenu.x + 20, positionMenu.y + 70);
        resumeBtn.setFillColor(sf::Color(100, 100, 250)); // Blue
        window.draw(resumeBtn);

        sf::Text resumeText;
        resumeText.setFont(font);
        resumeText.setString("Resume");
        resumeText.setCharacterSize(18);
        resumeText.setFillColor(sf::Color::White);
        resumeText.setPosition(resumeBtn.getPosition().x + 20, resumeBtn.getPosition().y + 5);
        window.draw(resumeText);

        // ---- BUTTON: Resume ----
        quitBtn.setSize(sf::Vector2f(width, height));
        quitBtn.setPosition(positionMenu.x + 20, positionMenu.y + 130);
        quitBtn.setFillColor(sf::Color(100, 100, 250)); // Blue
        window.draw(quitBtn);

        sf::Text quitText;
        quitText.setFont(font);
        quitText.setString("Quit");
        quitText.setCharacterSize(18);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(quitBtn.getPosition().x + 20, quitBtn.getPosition().y + 5);
        window.draw(quitText);

        // ---- BUTTON: RED FIREBALL ----
        redSprite.setTexture(player.getRedFireTexture());
        redSprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64)); // Initial frame (x,y,width,height)
        redSprite.setPosition(positionMenu.x + 20, positionMenu.y + 190);
        window.draw(redSprite);
        
        if (player.getSpell() == 1) {
            sf::RectangleShape redSpriteBorder;
            sf::Vector2f redSpriteSize(64.5f, 64.0f);
            sf::Color tempColor = sf::Color::Blue;
            redSpriteBorder.setSize(redSpriteSize);
            redSpriteBorder.setPosition(positionMenu.x + 20, positionMenu.y + 190);
            redSpriteBorder.setFillColor(sf::Color::Transparent);
            redSpriteBorder.setOutlineColor(tempColor);
            redSpriteBorder.setOutlineThickness(3.0f);
            window.draw(redSpriteBorder);
        }

        // ---- BUTTON: BLUE FIREBALL ----
        blueSprite.setTexture(player.getBlueFireTexture());
        blueSprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64)); // Initial frame (x,y,width,height)
        blueSprite.setPosition(positionMenu.x + 95, positionMenu.y + 190);
        window.draw(blueSprite);

        if (player.getSpell() == 2) {
            sf::RectangleShape blueSpriteBorder;
            sf::Vector2f blueSpriteSize(64.5f, 64.0f);
            sf::Color tempColor = sf::Color::Blue;
            blueSpriteBorder.setSize(blueSpriteSize);
            blueSpriteBorder.setPosition(positionMenu.x +95, positionMenu.y + 190);
            blueSpriteBorder.setFillColor(sf::Color::Transparent);
            blueSpriteBorder.setOutlineColor(tempColor);
            blueSpriteBorder.setOutlineThickness(3.0f);
            window.draw(blueSpriteBorder);
        }
    }
    
}

void GameManager::drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState& gameState) {
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
            //std::cout << "GAME PAUSED"<<std::endl;
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
            //std::cout << "GAME UNPAUSED"<<std::endl;
            keyManager.setEsc(false);
        }
        //resume button logic
        if (keyManager.getClickLeft()) {
            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            //std::cout << "Mouse clicked at: " << worldPos.x << ", " << worldPos.y << std::endl;
            //std::cout << "button at: " << resumeBtn.getPosition().x << ", " << resumeBtn.getPosition().y << std::endl;
            if (resumeBtn.getGlobalBounds().contains(worldPos)) {
                gameState = GameState::Playing;
                //std::cout << "Resume button clicked!\n";
            }
            if (quitBtn.getGlobalBounds().contains(worldPos)) {
                //std::cout << "Quit button clicked!\n";
                window.close();
            }
            if (redSprite.getGlobalBounds().contains(worldPos)) {
                // handle click
                player.setSpell(1);
            }
            if (blueSprite.getGlobalBounds().contains(worldPos)) {
                // handle click
                player.setSpell(2);
            }
        }

        drawGame(window, player, enemy, renderer, gameState);

    }
}