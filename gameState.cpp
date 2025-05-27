#include "gameState.h"



GameManager::GameManager(sf::RenderWindow& window, Player& player) :gameState(GameState::Playing) {
    if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
    }
    windowSize= sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y - window.getSize().y / 4.0f);

    // Convert screen-space size to world scale by applying the view's scaling
    view = sf::View(window.getView());
    float scaleX = view.getSize().x / window.getSize().x;
    float scaleY = view.getSize().y / window.getSize().y;
    worldSize= sf::Vector2f(windowSize.x * scaleX, windowSize.y * scaleY);
    positionMenu= sf::Vector2f(player.getPosX() * 100 - worldSize.x / 2.0f, player.getPosY() * 100 - worldSize.y / 2.0f);

    spawnBtn(window, player, gameState); //spawn menu; does not draw
}

void GameManager::spawnBtn(sf::RenderWindow& window, Player& player, GameState& gameState) {
    
    //menu border
    menuBorder.setSize(worldSize);
    menuBorder.setPosition(positionMenu);
    menuBorder.setFillColor(sf::Color(255, 0, 0, 100)); // red
    menuBorder.setOutlineColor(sf::Color::Red);
    menuBorder.setOutlineThickness(3.0f);
    //menu title
    title.setFont(font); // must be accessible from this scope
    title.setString("Game Paused");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(positionMenu.x + 20, positionMenu.y + 20);

    //create each button on menu
    resumeBtn = Button({ 150, 40 }, font, "Resume", false, positionMenu.x, positionMenu.y,1, 1); //1st button
    buttons.emplace_back(&resumeBtn);

    saveBtn = Button({ 150, 40 }, font, "Save", false, positionMenu.x, positionMenu.y,1, 2); //2nd button
    buttons.emplace_back(&saveBtn);

    loadBtn = Button({ 150, 40 }, font, "Load", false, positionMenu.x, positionMenu.y,1, 3); //3rd button
    buttons.emplace_back(&loadBtn);

    quitBtn = Button({ 150, 40 }, font, "Quit", false, positionMenu.x, positionMenu.y,1, 4); //4th button
    buttons.emplace_back(&quitBtn);


    //create equipment buttons

    redFBB = Button({ 64.5f, 64 }, font, "RedFireBall", false, positionMenu.x, positionMenu.y,1, 4);
    redFBB.sprite.setTexture(player.getRedFireTexture());
    redFBB.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));
    redFBB.sprite.setPosition(positionMenu.x + 20, positionMenu.y + 310);
    redFBB.rect.setPosition(positionMenu.x + 20, positionMenu.y + 310);
    equipment.emplace_back(&redFBB);


    blueFBB = Button({ 64.5f, 64 }, font, "BlueFireBall", false, positionMenu.x, positionMenu.y, 1, 4);
    blueFBB.sprite.setTexture(player.getBlueFireTexture());
    blueFBB.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));
    blueFBB.sprite.setPosition(positionMenu.x + 95, positionMenu.y + 310);
    blueFBB.rect.setPosition(positionMenu.x + 95, positionMenu.y + 310);
    equipment.emplace_back(&blueFBB);
}

void GameManager::updatePos(sf::Vector2f vec) {
    menuBorder.setPosition(vec);
    title.setPosition(vec.x + 20, vec.y + 20);
    auto& btns = getButtons();
    for (int i = 0; i < btns.size(); i++) {
        btns[i]->getRect()->setPosition(vec.x + 20, vec.y + 10 + (60 * (i + 1)));
        btns[i]->getText()->setPosition(btns[i]->getRect()->getPosition().x + 20, btns[i]->getRect()->getPosition().y + 5);

    }
    auto& equips = getEquipment();
    for (int j = 0; j < getEquipment().size(); j++) {
        equips[j]->getRect()->setPosition(vec.x + 20 + (65 * j), vec.y + 310);
        equips[j]->getSprite()->setPosition(vec.x + 20 + (65 * j), vec.y + 310);

    }
}

void GameManager::drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState) {
    //std::cout << "DRAW MENU CALLE1" << std::endl;
    if (gameState == GameState::Paused) {

        // RE-EVALUATE screen-space size to world scale by applying the view's scaling

        view = sf::View(window.getView());
        float scaleX = view.getSize().x / window.getSize().x;
        float scaleY = view.getSize().y / window.getSize().y;
        worldSize = sf::Vector2f(windowSize.x * scaleX, windowSize.y * scaleY);
        positionMenu = sf::Vector2f(player.getPosX() * 100 - worldSize.x / 2.0f, player.getPosY() * 100 - worldSize.y / 2.0f);

        updatePos(positionMenu);

        // ---- MENU & TITLE ----  
        window.draw(menuBorder);
        window.draw(title);

        // ---- BUTTON: Resume ----
        window.draw(resumeBtn.rect);
        window.draw(resumeBtn.btnText);

        // ---- BUTTON: Save ----
        window.draw(saveBtn.rect);
        window.draw(saveBtn.btnText);

        // ---- BUTTON: Load ----
        window.draw(loadBtn.rect);
        window.draw(loadBtn.btnText);

        // ---- BUTTON: Quit ----
        window.draw(quitBtn.rect);
        window.draw(quitBtn.btnText);

        // ---- BUTTON: RED FIREBALL ----
        window.draw(redFBB.sprite);
        if (player.getSpell() == 1) {
            redFBB.rect.setFillColor(sf::Color::Transparent);
            redFBB.rect.setOutlineColor(sf::Color::Blue);
            redFBB.rect.setOutlineThickness(3.0f);
            window.draw(redFBB.rect);
        }

        // ---- BUTTON: BLUE FIREBALL ----
        window.draw(blueFBB.sprite);
        if (player.getSpell() == 2) {
            blueFBB.rect.setFillColor(sf::Color::Transparent);
            blueFBB.rect.setOutlineColor(sf::Color::Blue);
            blueFBB.rect.setOutlineThickness(3.0f);
            window.draw(blueFBB.rect);
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
            if (resumeBtn.rect.getGlobalBounds().contains(worldPos)) {
                gameState = GameState::Playing;
                //std::cout << "Resume button clicked!\n";
            }
            if (saveBtn.rect.getGlobalBounds().contains(worldPos)) {
                // handle click
                //SAVE FILE SCRIPT HERE:
                std::cout << "SAVE CLICKED" << std::endl;
                saveBtn.active = true;

            }
            if (loadBtn.rect.getGlobalBounds().contains(worldPos)) {
                // handle click
                //LOAD FILE SCRIPT HERE: 
            }
            if (quitBtn.rect.getGlobalBounds().contains(worldPos)) {
                //std::cout << "Quit button clicked!\n";
                window.close();
            }
            if (redFBB.rect.getGlobalBounds().contains(worldPos)) {
                // handle click
                player.setSpell(1);
            }
            if (blueFBB.rect.getGlobalBounds().contains(worldPos)) {
                // handle click
                player.setSpell(2);
            }
        }
        drawGame(window, player, enemy, renderer, gameState);
    }
}