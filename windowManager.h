#pragma once
#include <SFML/Graphics.hpp>

//class Player;

class WindowManager {
public:
    // Constructor initializes the window
    WindowManager(int width, int height, const std::string& title);
    //ViewPort
    void processEvents();
    void updateView(bool left, bool right, bool up, bool down, float moveSpeed, float dt);  // Move the viewport
    //void applyView();  // Apply the updated view to the window

    // Function to return a reference to the window
    sf::RenderWindow& getWindow();
    void playerView(float playerX, float playerY, int squareSize);

private:
    sf::RenderWindow window;
    sf::View view;
    //Player& player;
};

