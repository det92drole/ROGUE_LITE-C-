#pragma once
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"
#include "render.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class Renderer;

struct Button {
	//ON BACK BURNER

	float x;
	float y;
	sf::Text btnText;
	std::string stringText;
	float height;
	float width;
	sf::Texture btnTexture;
	sf::RectangleShape rect;
	sf::Vector2f spriteSize;
	sf::Color fillColor;
	sf::Color borderColor;

};

enum class GameState {
	Playing,
	Paused,
	MainMenu,
	GameOver
};

class GameManager {
public:
	GameManager(sf::RenderWindow& window, Player& player);
	GameState gameState;
	sf::RectangleShape resumeBtn;
	sf::RectangleShape quitBtn;
	sf::Sprite redSprite;
	sf::Sprite blueSprite;
	sf::Vector2f worldPos; //mouse position
	sf::Vector2f worldSize; //referencing game window
	void drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState);
	void gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
		bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer);
	void drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState& gameState);
	
	std::unordered_map<std::string, Button> buttons;

private:
	sf::Font font;

	void spawnBtn(sf::RenderWindow& window, Player& player, GameState& gameState);

};


