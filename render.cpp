#include "render.h"
#include <iostream>
#include <bitset>

Renderer::Renderer(WindowManager& wm) : windowManager(wm){}
float scaleX = 0;
int squareSize = 100;
int mapW = x;
int mapH = y;

std::vector<sf::Sprite> spritesM;
std::vector<sf::Texture> textures(7);  // 0, 1, 2,3; wall, path, edge-path, player spawn;

void Renderer::drawGrid() {

    sf::RenderWindow& window = windowManager.getWindow();

    for (int i = 0; i < 7; ++i) {
        // Create binary filename like "0000.jpg", "0001.jpg", ..., "0101.jpg"
        std::string binaryFilename = "Assets/MapTiles/" + std::bitset<4>(i).to_string() + ".jpg";  // 4-bit binary string
        if (!textures[i].loadFromFile(binaryFilename)) {
            std::cerr << "Failed to load " << binaryFilename << std::endl;
        }
    }

    // Create a sprite for drawing each square
    for (auto& texture : textures) {
        spritesM.push_back(sf::Sprite(texture));  // Create a sprite for each texture
    }

    // Get the original size of the texture (or sprite's textureRect)
    sf::FloatRect spriteBounds = spritesM[0].getLocalBounds();

    float scaleX = static_cast<float>(squareSize) / spriteBounds.width;

    // Apply scale
    for (auto& sprite : spritesM) {
        sprite.setScale(scaleX, scaleX);
    }

    //draw tile map
    for (int col = 0; col < mapW; ++col) {
        for (int row = 0; row < mapH; ++row) {
            int posVal = grid[row][col];
            spritesM[posVal].setPosition(col * squareSize, row * squareSize); //x=col * squareSize, y=row * squareSize
            window.draw(spritesM[posVal]);

            sf::FloatRect bounds = spritesM[posVal].getGlobalBounds(); // Get sprite's bounds
            sf::RectangleShape border;
            border.setSize(sf::Vector2f(bounds.width, bounds.height));
            border.setPosition(bounds.left, bounds.top);
            border.setFillColor(sf::Color::Transparent); // No fill
            border.setOutlineColor(sf::Color::Blue);      // Border color
            border.setOutlineThickness(2.f);             // Border thickness


            window.draw(border);

        }
    }
}
