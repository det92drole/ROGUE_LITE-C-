#pragma once
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"
#include "render.h"
#include <SFML/Graphics.hpp>

class Renderer;


enum class GameState {
	Playing,
	Paused,
	MainMenu,
	GameOver
};

class GameManager {
public:
	GameManager();
	GameState gameState;
	sf::RectangleShape resumeBtn;
	sf::RectangleShape quitBtn;
	sf::Sprite redSprite;
	sf::Vector2f worldPos;
	void drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState);
	void gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
		bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer);
	void drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState& gameState);

private:
	sf::Font font;

};


