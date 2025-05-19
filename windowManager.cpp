#include "windowManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor: Initializes the SFML window
WindowManager::WindowManager(int width, int height, const std::string& title)
    : window(sf::VideoMode(width, height), title) {
    view.setSize(width, height); //matches view port to window size
    window.setView(view);  // Apply the view
}

void WindowManager::processEvents(KeyManager& keyManager) {
    sf::Event event;
    while (window.pollEvent(event)) {
        keyManager.update(event);  // Check for key presses

        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void WindowManager::updateView(bool left, bool right, bool up, bool down, float moveSpeed, float dt) {
    // Compute a single movement delta
    sf::Vector2f delta{ 0.f, 0.f };
    if (left)  delta.x -= moveSpeed*dt;
    if (right) delta.x += moveSpeed * dt;
    if (up)    delta.y -= moveSpeed * dt;
    if (down)  delta.y += moveSpeed * dt;

    // Only update the view once
    if (delta.x != 0.f || delta.y != 0.f) {
        view.move(delta);
        window.setView(view);
    }
}

void WindowManager::playerView(float playerX, float playerY, int squareSize) {
   float pX=playerX* squareSize;
   float pY = playerY * squareSize;
   //std::cout << "px: " << pX << " py: " << pY << std::endl;
   view.setCenter(sf::Vector2f(pX, pY));
   window.setView(view);
}

// Returns a reference to the window
sf::RenderWindow& WindowManager::getWindow() {
    return window;
}
