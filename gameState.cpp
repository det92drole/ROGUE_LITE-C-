#include "gameState.h"
#include "tinyfiledialogs.h"
#include <filesystem>


GameManager::GameManager(sf::RenderWindow& window, Player& player) :gameState(GameState::StartMenu) {
    if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
    }
    windowSize= sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y - window.getSize().y / 4.0f);

    // Convert screen-space size to world scale by applying the view's scaling
    view = sf::View(window.getView());
    uiView= sf::View((sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
    float scaleX = view.getSize().x / window.getSize().x;
    float scaleY = view.getSize().y / window.getSize().y;
    worldSize = sf::Vector2f((windowSize.x * scaleX) , (windowSize.y * scaleY));
    positionMenu= sf::Vector2f(player.getPosX() * 100 - worldSize.x / 2.0f, player.getPosY() * 100 - worldSize.y / 2.0f);

    spawnBtn(window, player, gameState); //spawn menu; does not draw
}

void GameManager::spawnBtn(sf::RenderWindow& window, Player& player, GameState& gameState) {
    
    //start menu
    startMenu = Menu();
    startMenuSize = { uiView.getSize().x, uiView.getSize().y}; 
    startMenu.menuWindow.setSize(startMenuSize);
    startMenu.menuWindow.setPosition(0, 0);
    startMenu.menuWindow.setFillColor(sf::Color::Black);
    startMenu.windowTitle.setFont(font); 
    startMenu.windowTitle.setString("Start Menu");
    startMenu.windowTitle.setCharacterSize(24);
    startMenu.windowTitle.setFillColor(sf::Color::White);
    startMenu.windowTitle.setPosition(((startMenuSize.x / 2) - 75.0f), 50);

    newGameBtn = Button({ 150, 40 }, font, "New Game", false, ((startMenuSize.x / 2) - 75.0f), (startMenuSize.y * 2 / 5), 1, 1, true);
    //buttons.emplace_back(&newGameBtn);

    //menu border
    menuBorder.setSize(worldSize);
    menuBorder.setPosition(positionMenu);
    menuBorder.setFillColor(sf::Color(255, 0, 0, 100)); // red
    menuBorder.setOutlineColor(sf::Color::Red);
    menuBorder.setOutlineThickness(3.0f);

    //pause menu title
    title.setFont(font); // must be accessible from this scope
    title.setString("Game Paused");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(positionMenu.x + 20, positionMenu.y + 20);

    //create each button on menu
    resumeBtn = Button({ 150, 40 }, font, "Resume", false, positionMenu.x, positionMenu.y,1, 1, true); //1st button
    buttons.emplace_back(&resumeBtn);

    saveBtn = Button({ 150, 40 }, font, "Save", false, positionMenu.x, positionMenu.y,1, 2, true); //2nd button
    buttons.emplace_back(&saveBtn);

    loadBtn = Button({ 150, 40 }, font, "Load", false, positionMenu.x, positionMenu.y,1, 3, true); //3rd button
    buttons.emplace_back(&loadBtn);

    quitBtn = Button({ 150, 40 }, font, "Quit", false, positionMenu.x, positionMenu.y,1, 4, true); //4th button
    buttons.emplace_back(&quitBtn);

    //status menu
    sf::Vector2f statusSize = { 208.5f, 64.0f }; //(64.5*3)+(5*3)
    sf::Vector2f statusPos = view.getCenter() - ((view.getSize() / 2.f));
    statusBarMenu = Menu();
    statusBarMenu.menuWindow.setSize(statusSize);
    statusBarMenu.menuWindow.setPosition(10,10);
    statusBarMenu.menuWindow.setFillColor(sf::Color(0, 0, 0, 100)); 
    statusBarMenu.menuWindow.setOutlineColor(sf::Color::Red);
    statusBarMenu.menuWindow.setOutlineThickness(3.0f);

    //health bar; 12.8h x 134w
    hpBarSize = { ((134.0f * player.getHealth()) / 100),12.8f};

    hpBar.setSize(hpBarSize);
    hpBar.setPosition(10 + 64.5 + 5, 12.8 * 2);
    hpBar.setFillColor(sf::Color(255, 0, 0, 255)); // red

    //mana bar
    manaBarSize = { 134.0f,12.8f };

    manaBar.setSize(manaBarSize);
    manaBar.setPosition(10 + 64.5 + 5, 12.8*4);
    manaBar.setFillColor(sf::Color(0, 0, 255, 255)); // red

    //spell equipped
    equippedSpell = Button({ 64.5,64.0 }, font, "E", true, 10, 10, 1, 1, true);
    equippedSpell.sprite.setPosition(10, 10);
    //create equipment buttons
    //
    redFBB = Button({ 64.5f, 64 }, font, "RedFireBall", true, positionMenu.x, positionMenu.y,1, 4, true);
    redFBB.sprite.setTexture(player.getRedFireTexture());
    redFBB.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));
    redFBB.sprite.setPosition(positionMenu.x + 20, positionMenu.y + 310);
    redFBB.rect.setPosition(positionMenu.x + 20, positionMenu.y + 310);
    equipment.emplace_back(&redFBB);

    blueFBB = Button({ 64.5f, 64 }, font, "BlueFireBall", true, positionMenu.x, positionMenu.y, 1, 4, true);
    blueFBB.sprite.setTexture(player.getBlueFireTexture());
    blueFBB.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));
    blueFBB.sprite.setPosition(positionMenu.x + 95, positionMenu.y + 310);
    blueFBB.rect.setPosition(positionMenu.x + 95, positionMenu.y + 310);
    equipment.emplace_back(&blueFBB);

    //create save menu
    saveWindow = Menu();
    saveWindow.menuWindow.setSize(worldSize);
    saveWindow.menuWindow.setPosition(positionMenu); //will cover main menu
    saveWindow.menuWindow.setFillColor(sf::Color(255,0,0,100)); //green

    //save menu title
    saveWindow.windowTitle.setFont(font); // must be accessible from this scope
    saveWindow.windowTitle.setString("Save Menu");
    saveWindow.windowTitle.setCharacterSize(24);
    saveWindow.windowTitle.setFillColor(sf::Color::White);
    saveWindow.windowTitle.setPosition(positionMenu.x + 20, positionMenu.y + 20);

    saveWindow.windowText.setFont(font); // must be accessible from this scope
    saveWindow.windowText.setString("Name your save");
    saveWindow.windowText.setCharacterSize(20);
    saveWindow.windowText.setFillColor(sf::Color::White);
    saveWindow.windowText.setPosition(positionMenu.x + 20, positionMenu.y + 60);

    //input box

    saveWindow.inputBox.setSize(sf::Vector2f(150, 40));
    saveWindow.inputBox.setPosition(positionMenu.x + 20, positionMenu.y + 90);
    saveWindow.inputBox.setFillColor(sf::Color::White);
    saveWindow.inputBox.setOutlineThickness(2);
    saveWindow.inputBox.setOutlineColor(sf::Color::Black);

    saveWindow.inputText.setFont(font);
    saveWindow.inputText.setCharacterSize(20);
    saveWindow.inputText.setFillColor(sf::Color::Black);
    saveWindow.inputText.setPosition(positionMenu.x + 25, positionMenu.y + 95);

    saveFileBtn = Button({ 75, 40 }, font, "Save", false, positionMenu.x+20, positionMenu.y+140, 1, 0, false); 
    saveButtons.emplace_back(&saveFileBtn);

    saveCancelBtn = Button({ 75, 40 }, font, "Cancel", false, positionMenu.x + 100, positionMenu.y + 140, 1, 0, false);
    saveButtons.emplace_back(&saveCancelBtn);

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
    saveWindow.menuWindow.setPosition(vec);
    saveWindow.windowTitle.setPosition(vec.x + 20, vec.y + 20);
    saveWindow.windowText.setPosition(vec.x + 20, vec.y + 60);
    saveWindow.inputBox.setPosition(vec.x + 20, vec.y + 90);
    saveWindow.inputText.setPosition(vec.x + 25, vec.y + 95);

    auto& saves = getSaveButtons();
    for (int k = 0; k < getSaveButtons().size(); k++) {
        saves[k]->getRect()->setPosition(vec.x + 20 + (80 * k), vec.y + 140);
        saves[k]->getText()->setPosition(saves[k]->getRect()->getPosition().x + 5, saves[k]->getRect()->getPosition().y + 5);
    }
}

void GameManager::drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState) {
    
    if (gameState != GameState::StartMenu) {
        //update HUD
        hpBarSize = { ((134.0f * player.getHealth()) / 100),12.8f };
        hpBar.setSize(hpBarSize);
        manaBarSize = { ((134.0f * player.getMana()) / 100),12.8f };
        manaBar.setSize(manaBarSize);

        // screen-space size to world scale by applying the view's scaling
        view = sf::View(window.getView());
        float scaleX = view.getSize().x / window.getSize().x;
        float scaleY = view.getSize().y / window.getSize().y;
        worldSize = sf::Vector2f(windowSize.x * scaleX, windowSize.y * scaleY);
        positionMenu = sf::Vector2f(player.getPosX() * 100 - worldSize.x / 2.0f, player.getPosY() * 100 - worldSize.y / 2.0f);
        //UPDATE menu pos as player moves through map
        updatePos(positionMenu);

        //----HUD START----
        window.setView(uiView);
        window.draw(statusBarMenu.menuWindow);
        window.draw(hpBar);
        window.draw(manaBar);
        window.draw(equippedSpell.sprite);
        //----HUD END----

        window.setView(view);
        if (gameState == GameState::Paused || gameState == GameState::GameOver) {

            if (gameState == GameState::Paused) {
                // ----SAVE MENU----
                if (saveBtn.active) {
                    window.draw(saveWindow.menuWindow);
                    window.draw(saveWindow.windowTitle);
                    window.draw(saveWindow.windowText);
                    window.draw(saveWindow.inputBox);
                    window.draw(saveWindow.inputText);

                    window.draw(saveFileBtn.rect);
                    window.draw(saveFileBtn.btnText);

                    window.draw(saveCancelBtn.rect);
                    window.draw(saveCancelBtn.btnText);

                }
                else {
                    // ---- MENU & TITLE ----  
                    window.draw(menuBorder);
                    window.draw(title);
                    auto& buttons = getButtons();
                    for (int i = 0; i < buttons.size(); i++) {
                        if (buttons[i]->getVisible()) {
                            window.draw(buttons[i]->rect);
                            window.draw(buttons[i]->btnText);
                        }
                    }

                    // ---- BUTTON: RED FIREBALL ----
                    window.draw(redFBB.sprite);
                    if (player.getSpell() == 1) {
                        redFBB.rect.setFillColor(sf::Color::Transparent);
                        redFBB.rect.setOutlineColor(sf::Color::Blue);
                        redFBB.rect.setOutlineThickness(3.0f);
                        equippedSpell.sprite.setTexture(player.getRedFireTexture());
                        equippedSpell.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));

                        window.draw(redFBB.rect);
                    }

                    // ---- BUTTON: BLUE FIREBALL ----
                    window.draw(blueFBB.sprite);
                    if (player.getSpell() == 2) {
                        blueFBB.rect.setFillColor(sf::Color::Transparent);
                        blueFBB.rect.setOutlineColor(sf::Color::Blue);
                        blueFBB.rect.setOutlineThickness(3.0f);
                        equippedSpell.sprite.setTexture(player.getBlueFireTexture());
                        equippedSpell.sprite.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));

                        window.draw(blueFBB.rect);
                    }
                }
            }
            if (gameState == GameState::GameOver) {
                // ---- MENU & TITLE ----  
                title.setString("GAME OVER");
                window.draw(menuBorder);
                window.draw(title);
                // ---- BUTTON: Load ----
                window.draw(loadBtn.rect);
                window.draw(loadBtn.btnText);

                // ---- BUTTON: Quit ----
                window.draw(quitBtn.rect);
                window.draw(quitBtn.btnText);
            }
        }
    }
    else { //if gameState==GameState::StartMenu
        //DRAW START MENU
        window.setView(uiView);
        startMenuSize = { uiView.getSize().x, uiView.getSize().y };
        window.draw(startMenu.menuWindow);
        window.draw(startMenu.windowTitle);

        newGameBtn.rect.setPosition(((startMenuSize.x / 2) - 75.0f), (startMenuSize.y* 2 / 5));
        newGameBtn.btnText.setPosition(((startMenuSize.x / 2) - 75.0f)+5, (startMenuSize.y * 2 / 5)+5);

        window.draw(newGameBtn.rect);
        window.draw(newGameBtn.btnText);

        auto& buttons = getButtons();
        for (int i = 2; i < buttons.size(); i++) {
            //buttons[i]->getVisible()
            buttons[i]->getRect()->setPosition(((startMenuSize.x / 2) - 75.0f), (startMenuSize.y*(i+1) / 5));
            buttons[i]->getText()->setPosition(((startMenuSize.x / 2) - 75.0f)+5, (startMenuSize.y* (i+1) / 5)+5);

            window.draw(buttons[i]->rect);
            window.draw(buttons[i]->btnText);
        }
    }
    
}

void GameManager::drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState& gameState) {
    renderer.drawGrid();
    player.draw(window);
    enemy.draw(window);
    drawMenu(window, player, gameState);
}

void saveToFile(std::string& filename, Player& player, Enemy& enemies) {
    std::ofstream outFile("Saves/" + filename + ".txt"); //create, open, overwrite

    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    //DEFINE SAVE DATA
    
    //DEFINE MAP DATA FOR SAVE
    std::string mapData = std::string("MAP") + "\n";

    outFile << mapData;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (grid[i][j] == 2) {
                outFile << "2"; //path touching wall
            }
            if (grid[i][j] == 0) {
                outFile << "0"; //wall
            }
            if (grid[i][j] == 1) {
                outFile << "1"; //path
            }
            if (grid[i][j] == 3) {
                outFile << "3"; //player spawn
            }
            if (grid[i][j] == 4) {
                outFile << "4"; //exit
            }
            if (grid[i][j] == 5) {
                outFile << "5"; //worm path
            }
            if (grid[i][j] == 6) {
                outFile << "6"; //item/key
            }
            if (grid[i][j] == 7) {
                outFile << "7"; //edge wall
            }
        }
        outFile << "\n";
    }
    outFile << "\n";

    //PLAYER SAVE
    std::string playerData = std::string("PLAYER") + "\n" + //type
        std::to_string(player.getSpell()) + "\n" + //player equiped spell
        std::to_string(player.getKeyCount()) + "\n" + //key count
        std::to_string(player.getPosX()) + "\n" + //player x pos
        std::to_string(player.getPosY()) + "\n" + //player y pos
        std::to_string(player.getHealth()) + "\n" + //hp
        std::to_string(player.getMana()) + "\n" + //mana
        "\n"; 

    outFile << playerData;

    //ENEMIES

    for (auto it = enemies.getEnemies().begin(); it != enemies.getEnemies().end(); ) {
        int agro = static_cast<int>(it->getAgro());
        std::string enemiesSave = 
            std::string("ENEMY") + "\n"+
            std::to_string(it->getID()) + "\n"+
            std::to_string(it->getPosX()) + "\n" +
            std::to_string(it->getPosY()) + "\n" +
            std::to_string(it->getSpeed()) + "\n" +
            std::to_string(it->getDirection()) + "\n" +
            std::to_string(agro) + "\n"+
            std::to_string(it->getTextSelect())+"\n";
        outFile << enemiesSave;
        outFile << "\n";
        ++it;
    }

    //END SAVE FUNC CLOSE FILE & COUT
    outFile.close();

    std::cout << "file saved" << std::endl;
}

void GameManager::loadFile(Player& player, Enemy& enemies, GameState& gameState) {
    //std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    const char* filters[] = { "*.txt" };
    const char* path = tinyfd_openFileDialog(
        "Select File",
        "Saves/",  // This sets initial directory + pre-fills the file
        1,
        filters,
        "Save Files (*.txt)",
        0);
    if (!path) {
        std::cout << "No file selected.\n";
        return;
    }
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return;
    }
    std::string label;
    std::string line;
    enemies.getEnemies().clear();
    grid.clear(); //empty current grid

    while (file >> label) {
        if (label == "MAP") {
            std::getline(file, line);  // skip rest of the "MAP" line
            while (std::getline(file, line)) {
                if (line.empty()) break; // stop on empty line
                std::vector<int> row;
                for (char c : line) {
                    if (isdigit(c)) {
                        row.push_back(c - '0');  // convert char to int
                    }
                }
                grid.push_back(row);
            }
        }
        else if (label == "PLAYER") {
            int spell, keyCount, hp;
            float xPos, yPos, mana;
            file >> spell >> keyCount >> xPos>> yPos>>hp>>mana;
            player.setSpell(spell);
            player.setKeyCount(keyCount);
            player.setPosX(xPos);
            player.setPosY(yPos);
            player.getSprite().setPosition(xPos * squareSize, yPos * squareSize);
            player.setHealth(hp);
            player.setMana(mana);

            //std::cout << "Player loaded to tile: (" << xPos << ", " << yPos << ")\n";
            //std::cout << "Sprite position: (" << xPos * squareSize << ", " << yPos * squareSize << ")\n";
        }
        else if (label == "ENEMY") {
            int ID, dir, agro, texture;
            float xPos, yPos, speed;
            file >> ID >> xPos >> yPos>>speed>>dir>>agro>>texture;
            Enemy enemy;
            enemy.setID(ID);
            enemy.setPosX(xPos);
            enemy.setPosY(yPos);
            enemy.setDirection(dir);
            enemy.setFrame(std::rand() % 8);
            enemy.setAgro(agro);
            enemy.setTextSelect(texture);

            switch (texture) {
            case 0: {
                //brain
                enemy.setWidthPx(60);
                enemy.setHeightPx(102);
                break;
            }
            case 1: {
                //red
                enemy.setWidthPx(78);
                enemy.setHeightPx(105);
                break;
            }
            case 2: {
                //tusk
                enemy.setWidthPx(66);
                enemy.setHeightPx(84);
                break;
            }
            }
            //std::cout << "Loaded " << Enemy::getTextures().size() << " enemy textures\n";
            //std::cout << "Assigning texture " << texture << " to enemy\n";
            if (texture < Enemy::getTextures().size()) {
                enemy.getSprite().setTexture(*Enemy::getTextures()[texture]);
            }
            enemy.getSprite().setPosition(xPos * squareSize, yPos * squareSize);
            enemy.getSprite().setTextureRect(sf::IntRect(enemy.getFrame() * enemy.getWidthPx(), 0, enemy.getWidthPx(), enemy.getHeightPx()));

            enemies.getEnemies().emplace_back(enemy);
        }
    }
    gameState = GameState::Paused;
    title.setString("Game Paused");

}

void GameManager::gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
    bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer) {
    if (player.getHealth() <= 0) {
        gameState = GameState::GameOver;
    }

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
        
        if (gameState == GameState::Paused) {
            if (keyManager.getEsc()) {
                gameState = GameState::Playing;
                //std::cout << "GAME UNPAUSED"<<std::endl;
                keyManager.setEsc(false);
            }
        }
        //resume button logic
        if (keyManager.getClickLeft()) {
            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            //std::cout << "Mouse clicked at: " << worldPos.x << ", " << worldPos.y << std::endl;
            //std::cout << "button at: " << resumeBtn.getPosition().x << ", " << resumeBtn.getPosition().y << std::endl;
            if (saveBtn.active) {
                if (saveWindow.inputBox.getGlobalBounds().contains(worldPos)) {
                    // handle click
                    saveWindow.target = true;
                    keyManager.saveMenu = true;
                    saveWindow.inputBox.setOutlineColor(sf::Color::Red);
                }
                else {
                    saveWindow.target = false;
                    saveWindow.inputBox.setOutlineColor(sf::Color::Black);
                }
                if (saveCancelBtn.rect.getGlobalBounds().contains(worldPos)) {
                    saveBtn.active = false;
                }
                if (saveFileBtn.rect.getGlobalBounds().contains(worldPos)) {
                    //save .txt file
                    saveToFile(keyManager.input, player, enemy);
                }
            }
            else {
                
                if (resumeBtn.rect.getGlobalBounds().contains(worldPos)) {
                    gameState = GameState::Playing;
                    //std::cout << "Resume button clicked!\n";
                }
                if (saveBtn.rect.getGlobalBounds().contains(worldPos)) {
                    //SAVE FILE SCRIPT HERE:
                    saveBtn.active = true;
                }
                if (loadBtn.rect.getGlobalBounds().contains(worldPos)) {
                    //LOAD FILE SCRIPT HERE: 
                    loadFile(player, enemy, gameState);
                }
                if (quitBtn.rect.getGlobalBounds().contains(worldPos)) {
                    //std::cout << "Quit button clicked!\n";
                    window.close();
                }
                if (redFBB.rect.getGlobalBounds().contains(worldPos)) {
                    player.setSpell(1);
                }
                if (blueFBB.rect.getGlobalBounds().contains(worldPos)) {
                    player.setSpell(2);
                }
            }
            keyManager.setClickLeft(false);
        }

        saveWindow.inputText.setString(keyManager.input);
        if (!saveBtn.active) {
            keyManager.input.clear();
        }

        drawGame(window, player, enemy, renderer, gameState);
    }
    else if (gameState == GameState::StartMenu) {
        //check for buttons
        window.setView(uiView);

        if (keyManager.getClickLeft()) {

            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (newGameBtn.rect.getGlobalBounds().contains(worldPos)) {
                std::cout << "New game button clicked!\n";
                startNewLevel(player, enemy);
                gameState = GameState::Paused;
            }
            if (loadBtn.rect.getGlobalBounds().contains(worldPos)) {
                //LOAD FILE SCRIPT HERE: 
                loadFile(player, enemy, gameState);
            }
            if (quitBtn.rect.getGlobalBounds().contains(worldPos)) {
                //std::cout << "Quit button clicked!\n";
                window.close();
            }
        }
    }
    else if (gameState == GameState::GameOver) {
        if (keyManager.getClickLeft()) {
            worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (loadBtn.rect.getGlobalBounds().contains(worldPos)) {
                //LOAD FILE SCRIPT HERE: 
                loadFile(player, enemy, gameState);
            }
            if (quitBtn.rect.getGlobalBounds().contains(worldPos)) {
                //std::cout << "Quit button clicked!\n";
                window.close();
            }
        }
        keyManager.setClickLeft(false);
    }
    drawGame(window, player, enemy, renderer, gameState);
}