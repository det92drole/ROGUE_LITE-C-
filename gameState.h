#pragma once
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"
#include "render.h"

class Renderer;


enum class GameState {
	Playing,
	Paused,
	MainMenu,
	GameOver
};

class GameManager {
public:
	GameState gameState = GameState::Playing;
	void drawMenu(sf::RenderWindow& window, Player& player, GameState gameState);
	void gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
		bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer);
	void drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState gameState);
};


