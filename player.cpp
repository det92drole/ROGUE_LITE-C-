#include "player.h"
#include <iostream>
#include "rand.h"

Player::Player() : playerHealth(100), frame(0), frameTime(0.2f), elapsedTime(0.0f), playerPosX(spawnFloatX), playerPosY(spawnFloatY), canMove(false) {
	if (!loadTextures()) {
		std::cerr << "Error: Failed to load one or more player textures.\n";
		// Optional: handle error, e.g., set a fallback texture or throw an exception
	}

	direction = 0; //0 up, 1 right, 2 down, 3 left
	sprite.setTexture(tU);// default texture player faces up

	sprite.setTextureRect(sf::IntRect(0, 0, 48, 68)); // Initial frame (x,y,width,height)
}

sf::Clock fireCooldownClock;  // measures time since last fire
float fireCooldown = 0.5f;    // minimum seconds between shots

FireBall Player::createFireBall(float spawnX, float spawnY) {
	//std::cout << "Fire FireBall" << std::endl;
	FireBall newFB;
	newFB.x = spawnX;
	newFB.y = spawnY;
	newFB.spriteBall.setTexture(tF);
	newFB.spriteBall.setPosition(newFB.x * squareSize, newFB.y * squareSize);
	newFB.spriteBall.setTextureRect(sf::IntRect(0, 0, 64.5f, 64));
	return newFB;
}

Item Player::createKey(float x, float y) {
	Item newKey;
	newKey.x = x;
	newKey.y = y;
	newKey.itemSprite.setTexture(tKey);
	newKey.itemSprite.setPosition(newKey.x * squareSize, newKey.y * squareSize);
	newKey.itemSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	newKey.itemSprite.setScale(2.0f, 2.0f);  // (x scale, y scale)
	return newKey;
}

void Player::update(sf::Time deltaTime, bool left, bool right, bool up, bool down, bool space) {
	//this function listens for keystrokes
	//creates fireballs based on keystrokes
	//updates player movement/animations and fireballs animations

	elapsedTime += deltaTime.asSeconds();
	int intPlayerX = static_cast<int>(getPosX());
	int intPlayerY = static_cast<int>(getPosY());

	if (left) {
		direction = 3;
		moveSpeed = 0.02f;

		if(canMove) {
			//if not illegal move, then move
			playerPosX -= moveSpeed;
			sprite.setTexture(tL);// change texture for left move
		}
	}

	if (right) {
		direction = 1;
		moveSpeed = 0.02f;

		if(canMove) {
			//if not illegal move, then move
			playerPosX += moveSpeed;
			sprite.setTexture(tR);// change texture for up move
		}
	}

	if (up) {
		direction = 0;
		moveSpeed = 0.02f;

		if(canMove) {
			//if not illegal move, then move
			playerPosY -= moveSpeed;
			sprite.setTexture(tU);// change texture for up move
		}
	}

	if (down) {
		direction = 2;
		moveSpeed = 0.02f;

		if(canMove) {
			//if not illegal move, then move
			playerPosY += moveSpeed;
			sprite.setTexture(tD);// change texture for up move
		}
	}

	if (left || right || up || down) { //remains bool incase movement key is NOT pressed; this will allow idle
		if (elapsedTime >= frameTime) {
			frame = (frame + 1) % 4;
			sprite.setTextureRect(sf::IntRect(frame * 48, 0, 48, 68));
			elapsedTime = 0.0f;
		}
	}
	else { //idle animation here
		sprite.setTextureRect(sf::IntRect(0, 0, 48, 68));
	}

	if (spaceBar && fireCooldownClock.getElapsedTime().asSeconds() > fireCooldown) {

		switch (direction) {
			case 3:
			{
				// only left true left
				FireBall newFireball = createFireBall(getPosX(), getPosY());

				newFireball.direction = 3;
				newFireball.speed = -0.1f;
				newFireball.widthPx=64.5;
				newFireball.heightPx=64;
				getFireBalls().push_back(newFireball);

				break;
			}
			case 1:
			{
				// only right true right
				FireBall newFireball = createFireBall(getPosX(), getPosY());

				newFireball.direction = 1;
				newFireball.speed = 0.1f;
				newFireball.widthPx = 64.5;
				newFireball.heightPx = 64;
				getFireBalls().push_back(newFireball);
				break;
			}
			case 0:
			{
				// only up true up
				FireBall newFireball = createFireBall(getPosX(), getPosY());

				newFireball.direction = 0;
				newFireball.speed = -0.1f;
				newFireball.widthPx = 64.5;
				newFireball.heightPx = 64;
				getFireBalls().push_back(newFireball);
				break;
			}
			case 2:
			{
				// only down true down
				FireBall newFireball = createFireBall(getPosX(), getPosY());

				newFireball.direction = 2;
				newFireball.speed = 0.1f;
				newFireball.widthPx = 64.5;
				newFireball.heightPx = 64;
				getFireBalls().push_back(newFireball);
				break;
			}
			default:
				// unknown
				//do not fire
				break;
			}
		// Reset the cooldown clock
		fireCooldownClock.restart();
	}

	for (auto it = getFireBalls().begin(); it != getFireBalls().end(); ) {
		//update sprite frame
		it->elapsedTime += deltaTime.asSeconds();

		if (it->direction>=0) {
			if (it->elapsedTime >= frameTime) {
				it->frame = (it->frame + 1) % 4;
				it->spriteBall.setTextureRect(sf::IntRect(it->frame * 64.5f, 0, 64.5f, 64.0f));
				it->elapsedTime = 0.0f;
			}
		}
		++it;
		
	}
	//for (const auto& fireball : fireBalls) {
	//	std::cout << "pos x: "<<fireball.x <<", pos y: " << fireball.y << std::endl;  
	//}
}

//START REFERENCE: fireball collision moved to collisionmanager.cpp
/*
		//fireball collision detection with walls
		//removal of fireball when collision detected
		//update firebal x,y to move pos
		int tempX = static_cast<int>(it->x);
		int tempY = static_cast<int>(it->y);

		switch (it->direction) {
			case 3:{
				// only left true
				bool canMove = true;
				if (tempX <= 0) {
				it = getFireBalls().erase(it);
				break;
				}
				bool hitWallSide = !grid[tempY][tempX - 1] && it->x <= tempX + it->epsilon;
				bool hitWallCorner = !grid[tempY + 1][tempX - 1] && (tempY + 1) != y - 1 &&
					it->x <= tempX + it->epsilon && it->y + .64f >= tempY + 1;

				if (hitWallSide || hitWallCorner) {
					it = getFireBalls().erase(it);
					canMove = false;
				}
				if (canMove) {
					it->x += it->speed;
					++it;
				}
				break;
			}
			case 1:{
				// only right true
				bool canMove = true;
				if (tempX >= grid[0].size() - 1) {
				it = getFireBalls().erase(it);
				break;
			}
				bool hitWallSide = !grid[tempY][tempX + 1] && it->x + .645f >= tempX + 1 - it->epsilon;
				bool hitWallCorner = !grid[tempY + 1][tempX + 1] && (tempY + 1) != y - 1 &&
					it->x + .645f >= tempX + 1 - it->epsilon && it->y + .64f >= tempY + 1;

				if (hitWallSide || hitWallCorner) {
					it = getFireBalls().erase(it);
					canMove = false;
				}
				if (canMove) {
					it->x += it->speed;
					++it;
				}
				break;
			}
			case 0:{
				// only up true
				bool canMove = true;
				if (tempY <= 0) {
				it = getFireBalls().erase(it);
				break;
			}
				bool hitWallSide = !grid[tempY - 1][tempX] && it->y <= tempY + it->epsilon;
				bool hitWallCorner = !grid[tempY - 1][tempX + 1] && (tempX + 1) != x - 1 &&
					it->y <= tempY + it->epsilon && it->x + .645f >= tempX + 1;

				if (hitWallSide || hitWallCorner) {
					it = getFireBalls().erase(it);
					canMove = false;
				}

				if (canMove) {
					it->y += it->speed;
					++it;
				}
				break;
			}
			case 2: {//0
				// only down true
				bool canMove = true;
				if (tempY + 1 >= grid.size()) {
				it = getFireBalls().erase(it);
				break;
			}
				bool hitWallSide = !grid[tempY + 1][tempX] && it->y + .64f >= tempY + 1 - it->epsilon;
				bool hitWallCorner = !grid[tempY + 1][tempX + 1] && (tempX + 1) != x - 1 &&
					it->y + .64f >= tempY + 1 - it->epsilon && it->x + .645f >= tempX + 1;

				if (hitWallSide || hitWallCorner) {
					it = getFireBalls().erase(it);
					canMove = false;
				}
				if (canMove) {
					it->y += it->speed;
					++it;
				}
				break;
			}
			default:
				// all true
				//should not happen
				break;
		}
		*/
//END REFERENCE

void Player::draw(sf::RenderWindow& window) {
	sprite.setPosition(playerPosX * squareSize, playerPosY * squareSize);
	window.draw(sprite);
	for (auto it = getFireBalls().begin(); it != getFireBalls().end(); ++it) {
		it->spriteBall.setPosition(it->x * squareSize, it->y * squareSize);
		window.draw(it->spriteBall);
	}
	for (auto it = getKeys().begin(); it != getKeys().end(); ++it) {
		it->itemSprite.setPosition(it->x * squareSize, it->y * squareSize);
		window.draw(it->itemSprite);
	}
	
}

int Player::getHealth() const {
	return playerHealth;
}

void Player::setHealth(int health) {
	playerHealth = health;
}

void Player::changeXY(float x, float y) {
	playerPosY = y;
	playerPosX = x;
	//std::cout << "CHANGED SPAWN VALUE" << std::endl;
}
std::vector<Player> Player::playerArr;

void Player::testArrPlayer() {
	Player::getPlayers().clear();
	Player::getPlayers().resize(50);

	std::cout << "players test() call: " << getPlayers().size() << std::endl;
}

std::vector<Player>& Player::getPlayers() {
	return playerArr;
}

bool Player::loadTextures() {
	return tD.loadFromFile("Assets/Player/playerDown.png") &&
		tR.loadFromFile("Assets/Player/playerRight.png") &&
		tL.loadFromFile("Assets/Player/playerLeft.png") &&
		tU.loadFromFile("Assets/Player/playerUp.png") &&
		tF.loadFromFile("Assets/Player/fireball.png") &&
		tKey.loadFromFile("Assets/Player/key.png");
}
