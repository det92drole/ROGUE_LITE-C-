#pragma once
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"

enum class GameState {
	Playing,
	Paused,
	MainMenu,
	GameOver
};

class GameManager {
public:
	GameState gameState = GameState::Playing;

	void gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager);
};


