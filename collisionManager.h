#pragma once
#include "player.h"
#include "rand.h"
#include "enemies.h"

void collisions(Player& player, int exitX, int exitY, int direction, Enemy& enemy, sf::Time deltaTime);

void startNewLevel(Player& player, Enemy& enemy);