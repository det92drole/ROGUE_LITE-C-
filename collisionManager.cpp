#include "collisionManager.h"

float buffer = 0.02f;
float epsilon = 0.02f;

void startNewLevel(Player& player, Enemy& enemy) {
	popGrid();
	player.setPosX(spawnFloatX);
	player.setPosY(spawnFloatY);
	enemy.spawnEnemies();
}

bool pointInBox(float fX, float fY, float fH, float fW, float eX, float eY, float eH, float eW) {
	float p1x = fX;
	float p1y = fY;
	float p2x = fX + fW;
	float p2y = fY;
	float p3x = fX + fW;
	float p3y = fY + fH;
	float p4x = fX;
	float p4y = fY + fH;

	float q1x = eX;
	float q1y = eY;
	float q2x = eX + eW;
	float q2y = eY;
	float q3x = eX + eW;
	float q3y = eY + eH;
	float q4x = eX;
	float q4y = eY + eH;

	float qMinX = std::min(q1x, q2x);
	float qMaxX = std::max(q1x, q2x);
	float qMinY = std::min(q1y, q4y);
	float qMaxY = std::max(q1y, q4y);

	return (fX > qMinX) && (fX < qMaxX) && (fY > qMinY) && (fY < qMaxY);
}

void checkPlayerWall(Player& player, int exitX, int exitY, int direction, Enemy& enemy) {
	//only changes made to player are x and y
	// can also reset map on level exit
	int intPlayerX = static_cast<int>(player.getPosX());
	int intPlayerY = static_cast<int>(player.getPosY());

	player.setCanMove(true);

	switch (direction) {
	case 3:
		// left collision logic
		if (grid[intPlayerY][intPlayerX - 1] == 0) { //if value zero; then cannot walk
			//NOT legal move into gridMap[intPlayerX][intPlayerY]
			//std::cout << "not legal LEFT" << std::endl;
			//std::cout << "player pos: "<< getPosX() << " wall X: "<<intPlayerX << std::endl;
			if (player.getPosX() <= intPlayerX + epsilon) {
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosX(intPlayerX + buffer);
				player.setCanMove(false);
			}
		}

		if (grid[intPlayerY + 1][intPlayerX - 1] == 0 && (intPlayerY + 1) != y - 1) {
			//check if feet touch
			//std::cout << "intPlayerY + 1; " << intPlayerY + 1 << " getPosY: "<< getPosY() << " y: " << y << std::endl;
			if (player.getPosX() <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//std::cout << "feet touch" << std::endl;
				player.setPosX(intPlayerX + buffer);
				player.setCanMove(false);
			}
		}
		//check for exit
		if (grid[intPlayerY][intPlayerX - 1] == 4) { 
			if (player.getPosX() <= intPlayerX+epsilon) {
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX - 1] == 4 && (intPlayerY + 1) != y - 1) {
			if (player.getPosX() <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		break;
	case 1:
		// right logic
		if (!grid[intPlayerY][intPlayerX + 1]) {
			//NOT legal move
			//std::cout << "not legal RIGHT" << std::endl;
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon) {//player sprite is 48 pix wide devided by 100 squareSize
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				//std::cout << "pos: "<< getPosX()<< " pos + mod: " << getPosX() + .48 <<"intPlayerX: "<<intPlayerX<< "wall : " << intPlayerX + 1 << std::endl;
				player.setPosX(intPlayerX + .52 - buffer); // 1-.48=.52; .52+.05 (buffer)
				player.setCanMove(false);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX + 1] == 0 && (intPlayerY + 1) != y - 1) {
			//check if feet touch
			//std::cout << "intPlayerY + 1; " << intPlayerY + 1 << " getPosY: "<< getPosY() << " y: " << y << std::endl;
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//std::cout << "feet touch" << std::endl;
				player.setPosX(intPlayerX + .52 - buffer);
				player.setCanMove(false);
			}
		}
		//check for exit
		if (grid[intPlayerY][intPlayerX + 1] == 4) {
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon) {//player sprite is 48 pix wide devided by 100 squareSize
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX + 1] == 4 && (intPlayerY + 1) != y - 1) {
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		break;
	case 0:
		// up logic
		if (!grid[intPlayerY - 1][intPlayerX]) {
			//NOT legal move
			//std::cout << "not legal UP" << std::endl;
			if (player.getPosY() <= intPlayerY + epsilon) {
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + buffer);
				player.setCanMove(false);
			}
		}
		if (!grid[intPlayerY - 1][intPlayerX + 1] && (intPlayerX + 1) != x - 1) {
			//NOT legal move
			//std::cout << "not legal UP" << std::endl;
			if (player.getPosY() <= intPlayerY + epsilon && player.getPosX() + .48 >= intPlayerX + 1) {
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + buffer);
				player.setCanMove(false);
			}
		}

		//check for exit
		if (grid[intPlayerY - 1][intPlayerX] == 4) {
			if (player.getPosY() <= intPlayerY + epsilon) {
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		if (grid[intPlayerY - 1][intPlayerX + 1] == 4 && (intPlayerX + 1) != x - 1) {
			if (player.getPosY() <= intPlayerY + epsilon && player.getPosX() + .48 >= intPlayerX + 1) {
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		break;
	case 2:
		// down logic
		if (!grid[intPlayerY + 1][intPlayerX]) {
			//NOT legal move
			//std::cout << "not legal DOWN" << std::endl;
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + .32 - buffer);
				player.setCanMove(false);
			}
		}
		if (!grid[intPlayerY + 1][intPlayerX + 1] && (intPlayerX + 1) != x - 1) {
			//NOT legal move
			//std::cout << "not legal DOWN" << std::endl;
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon && player.getPosX() + .48 >= intPlayerX + 1) { //player sprite is 68 pix wide
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + .32 - buffer);
				player.setCanMove(false);
			}
		}

		//check for exit
		if (grid[intPlayerY + 1][intPlayerX] == 4) {
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX + 1] == 4 && (intPlayerX + 1) != x - 1) {
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon && player.getPosX() + .48 >= intPlayerX + 1) { //player sprite is 68 pix wide
				//popGrid();
				startNewLevel(player, enemy);
			}
		}
		break;
	default:
		player.setCanMove(false);
		break;
	}
}

void checkEnemyWall(Enemy& enemy, sf::Time deltaTime, Player& player) {
	//only changes to enemies is direction, speed, x, y
	if (enemy.getEnemies().size() != 0) {
		if (enemy.getEnemies()[0].getAgro()) { //if enemy agro; movement directed to player
			for (auto it = enemy.getEnemies().begin(); it != enemy.getEnemies().end(); ) {
				int tempX = static_cast<int>(it->getPosX());
				int tempY = static_cast<int>(it->getPosY());
				it->setSpeed(0); //movement no longer determined by speed


				float xT = player.getPosX() + (((player.getSprite().getGlobalBounds().width / 100.0f) / 2.0f) - ((it->getWidthPx() / 100.0f) / 2.0f));
				float yT = player.getPosY() + (((player.getSprite().getGlobalBounds().height / 100.0f) / 2.0f) - ((it->getHeightPx() / 100.0f) / 2.0f));
				float vecx = xT - it->getPosX();
				float vecy = yT - it->getPosY();
				float hypotenuse = std::hypot(vecx, vecy);
				if (hypotenuse != 0) {
					float dirX = vecx / hypotenuse;
					float dirY = vecy / hypotenuse;
					it->setPosX(it->getPosX() + dirX*deltaTime.asSeconds());
					it->setPosY(it->getPosY() + dirY*deltaTime.asSeconds());
					std::cout << "dirx: " << dirX << " dirY: " << dirY << std::endl;

				}
				//std::cout <<"enemy id: "<<it->getID()<< " enemy x: " << it->getPosX() << " enemy Y: " << it->getPosY() << std::endl;
				//std::cout << "player x: " << player.getPosX() << " player y: " << player.getPosY() << std::endl;

				++it;
			}
		}
		else { //normal movement
			for (auto it = enemy.getEnemies().begin(); it != enemy.getEnemies().end(); ) {
				int tempX = static_cast<int>(it->getPosX());
				int tempY = static_cast<int>(it->getPosY());

				switch (it->getDirection()) {
				case 3: {
					//only left true
					it->setPosX(it->getPosX() + (it->getSpeed() * deltaTime.asSeconds()));

					if (tempX <= 0) {
						it->setSpeed(it->getSpeed() * -1);
						it->setDirection(1);
					}
					else {
						bool hitWallSide = !grid[tempY][tempX - 1] && it->getPosX() <= tempX + it->getEpsilon();
						bool hitWallCorner = !grid[tempY + 1][tempX - 1] && (tempY + 1) != y - 1 &&
							it->getPosX() <= tempX + it->getEpsilon() && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;
						if (hitWallSide || hitWallCorner) {
							it->setSpeed(it->getSpeed() * -1);
							it->setDirection(1);
						}
					}
					break;
				}
				case 1: {
					// only right true 
					it->setPosX(it->getPosX() + (it->getSpeed() * deltaTime.asSeconds()));
					if (tempX >= grid[0].size() - 1) {
						it->setSpeed(it->getSpeed() * -1);
						//logg << "Speed after: " << it->speed << std::endl;					
						it->setDirection(3);
					}
					else {
						bool hitWallSide = !grid[tempY][tempX + 1] && it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - it->getEpsilon();
						bool hitWallCorner = !grid[tempY + 1][tempX + 1] && (tempY + 1) != y - 1 &&
							it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - it->getEpsilon() && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;

						if (hitWallSide || hitWallCorner) {
							//logg << "hit" << std::endl;
							//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
							//logg << "Speed before: " << it->speed << std::endl;
							it->setSpeed(it->getSpeed() * -1);
							//logg << "Speed after: " << it->speed << std::endl;					
							it->setDirection(3);
						}
					}
					break;
				}
				case 0: {
					// only up true
					it->setPosY(it->getPosY() + (it->getSpeed() * deltaTime.asSeconds()));

					if (tempY <= 0) {
						it->setSpeed(it->getSpeed() * -1);
						//logg << "Speed after: " << it->speed << std::endl;					
						it->setDirection(2);
					}
					else {
						bool hitWallSide = !grid[tempY - 1][tempX] && it->getPosY() <= tempY + it->getEpsilon();
						bool hitWallCorner = !grid[tempY - 1][tempX + 1] && (tempX + 1) != x - 1 &&
							it->getPosY() <= tempY + it->getEpsilon() && it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;

						if (hitWallSide || hitWallCorner) {
							//logg << "hit" << std::endl;
							//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
							//logg << "Speed before: " << it->speed << std::endl;
							it->setSpeed(it->getSpeed() * -1);
							//logg << "Speed after: " << it->speed << std::endl;					
							it->setDirection(2);
						}
					}
					break;
				}
				case 2: {
					// only down true
					it->setPosY(it->getPosY() + (it->getSpeed() * deltaTime.asSeconds()));

					if (tempY >= grid.size() - 1) {
						it->setSpeed(it->getSpeed() * -1);
						//logg << "Speed after: " << it->speed << std::endl;
						it->setDirection(0);

					}
					else {
						bool hitWallSide = !grid[tempY + 2][tempX] && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - it->getEpsilon();
						bool hitWallCorner = !grid[tempY + 2][tempX + 1] && (tempX + 1) != x - 1 &&
							it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - it->getEpsilon() && it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;

						if (hitWallSide || hitWallCorner) {
							//logg << "hit" << std::endl;
							//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
							//logg << "Speed before: " << it->speed << std::endl;
							it->setSpeed(it->getSpeed() * -1);
							//logg << "Speed after: " << it->speed << std::endl;
							it->setDirection(0);
						}
					}
					break;
				}
				default:
					// all true
					//should not happen
					break;
				}

				++it;
			}
		}
	}
}


void updateFireBalls(Player& player, Enemy& enemy) {
	auto& fireballs = player.getFireBalls();
	auto& enemies = enemy.getEnemies();

	for (auto it = fireballs.begin(); it != fireballs.end(); ) {
		bool eraseFireball = false;

		int tempX = static_cast<int>(it->getX());
		int tempY = static_cast<int>(it->getY());

		// === 1. WALL COLLISION AND MOVEMENT ===
		switch (it->direction) {
		case 3: { // LEFT
			if (tempX <= 0 ||
				(!grid[tempY][tempX - 1] && it->getX() <= tempX + it->getEpsilon()) ||
				(!grid[tempY + 1][tempX - 1] && tempY + 1 != y - 1 &&
					it->getX() <= tempX + it->getEpsilon() && it->getY() + .64f >= tempY + 1)) {
				eraseFireball = true;
			}
			else {
				it->setX(it->getX() + it->getSpeed());
			}
			break;
		}
		case 1: { // RIGHT
			if (tempX >= grid[0].size() - 1 ||
				(!grid[tempY][tempX + 1] && it->getX() + .645f >= tempX + 1 - it->getEpsilon()) ||
				(!grid[tempY + 1][tempX + 1] && tempY + 1 != y - 1 &&
					it->getX() + .645f >= tempX + 1 - it->getEpsilon() &&
					it->getY() + .64f >= tempY + 1)) {
				eraseFireball = true;
			}
			else {
				it->setX(it->getX() + it->getSpeed());
			}
			break;
		}
		case 0: { // UP
			if (tempY <= 0 ||
				(!grid[tempY - 1][tempX] && it->getY() <= tempY + it->getEpsilon()) ||
				(!grid[tempY - 1][tempX + 1] && tempX + 1 != x - 1 &&
					it->getY() <= tempY + it->getEpsilon() && it->getX() + .645f >= tempX + 1)) {
				eraseFireball = true;
			}
			else {
				it->setY(it->getY() + it->getSpeed());
			}
			break;
		}
		case 2: { // DOWN
			if (tempY + 1 >= grid.size() ||
				(!grid[tempY + 1][tempX] && it->getY() + .64f >= tempY + 1 - it->getEpsilon()) ||
				(!grid[tempY + 1][tempX + 1] && tempX + 1 != x - 1 &&
					it->getY() + .64f >= tempY + 1 - it->getEpsilon() &&
					it->getX() + .645f >= tempX + 1)) {
				eraseFireball = true;
			}
			else {
				it->setY(it->getY() + it->getSpeed());
			}
			break;
		}
		}

		if (eraseFireball) {
			it = fireballs.erase(it);
			continue;
		}

		// === 2. ENEMY COLLISION ===
		bool hitEnemy = false;
		for (auto e = enemies.begin(); e != enemies.end(); ) {
			float eX = e->getPosX();
			float eY = e->getPosY();
			float eW = static_cast<float>(e->getWidthPx()) / 100;
			float eH = static_cast<float>(e->getHeightPx()) / 100;

			float fX = it->getX();
			float fY = it->getY();
			float fW = it->getWidth() / 100;
			float fH = it->getHeight() / 100;

			bool overlap =
				fX < eX + eW && fX + fW > eX &&
				fY < eY + eH && fY + fH > eY;

			if (overlap) {
				std::cout << "HIT" << std::endl;
				e = enemies.erase(e);
				hitEnemy = true;
				break; // one enemy per fireball
			}
			else {
				++e;
			}
		}

		if (hitEnemy) {
			it = fireballs.erase(it);
			for (auto e = enemies.begin(); e != enemies.end(); ) {
				e->setAgro(true);
				++e;
			}
		}
		else {
			++it;
		}
	}
}

void collisions(Player& player, int exitX, int exitY, int direction, Enemy& enemy, sf::Time deltaTime) {
	checkPlayerWall(player, exitX, exitY, direction, enemy);
	checkEnemyWall(enemy, deltaTime, player);
	updateFireBalls(player, enemy);
}