#include "collisionManager.h"

float buffer = 0.02f;
float epsilon = 0.02f;
float hitPush = .32f;

void startNewLevel(Player& player, Enemy& enemy) {
	//std::cout << "key count: " << player.getKeyCount() << std::endl;
	player.getKeys().clear();
	popGrid();
	player.setPosX(spawnFloatX);
	player.setPosY(spawnFloatY);
	enemy.spawnEnemies();
	player.getKeys().emplace_back(player.createKey(keyX, keyY));
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

	if ((p1x > qMinX) && (p1x < qMaxX) && (p1y > qMinY) && (p1y < qMaxY)) {
		//if top left corner hits target
		return true;
	}
	if ((p2x > qMinX) && (p2x < qMaxX) && (p2y > qMinY) && (p2y < qMaxY)) {
		//if top right corner
		return true;
	}
	if ((p3x > qMinX) && (p3x < qMaxX) && (p3y > qMinY) && (p3y < qMaxY)) {
		//if bottom right
		return true;
	}
	if ((p4x > qMinX) && (p4x < qMaxX) && (p4y > qMinY) && (p4y < qMaxY)) {
		//if bottom left
		return true;
	}
	return false;
}

bool hitWall(Player& player, int moveDir) {
	int intPlayerX = static_cast<int>(player.getPosX());
	int intPlayerY = static_cast<int>(player.getPosY());

	switch (moveDir) 
	{
	case 0:
	{
		if ((grid[intPlayerY - 1][intPlayerX] == 0) || (grid[intPlayerY - 1][intPlayerX] == 7)) {
			if (player.getPosY() - hitPush <= intPlayerY + epsilon) {
				return true;
			}
			else {
				return false;
			}
		}else if ((grid[intPlayerY - 1][intPlayerX + 1] == 0 && (intPlayerX + 1) != x - 1) ||
			(grid[intPlayerY - 1][intPlayerX + 1] == 7 && (intPlayerX + 1) != x - 1)) {
			if (player.getPosY() - hitPush <= intPlayerY + epsilon && player.getPosX() + .48 >= intPlayerX + 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	}

	case 1:
	{
		if ((grid[intPlayerY][intPlayerX + 1] == 0) || (grid[intPlayerY][intPlayerX + 1] == 7)) {
			if (player.getPosX() + .48+hitPush >= intPlayerX + 1 - epsilon) {//player sprite is 48 pix wide devided by 100 squareSize
				return true;
			}
			else {
				return false;
			}
		}else if ((grid[intPlayerY + 1][intPlayerX + 1] == 0 && (intPlayerY + 1) != y - 1) ||
			(grid[intPlayerY + 1][intPlayerX + 1] == 7 && (intPlayerY + 1) != y - 1)) {
			if (player.getPosX() + .48+hitPush >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	}
	case 2:
	{
		if ((grid[intPlayerY + 1][intPlayerX] == 0) || (grid[intPlayerY + 1][intPlayerX] == 7)) {
			if (player.getPosY() +hitPush+ .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
				return true;
			}
			else {
				return false;
			}
		}else if ((grid[intPlayerY + 1][intPlayerX + 1] == 0 && (intPlayerX + 1) != x - 1) ||
			(grid[intPlayerY + 1][intPlayerX + 1] == 7 && (intPlayerX + 1) != x - 1)) {
			if (player.getPosY() + .68 +hitPush>= intPlayerY + 1 - epsilon && player.getPosX() + .48 >= intPlayerX + 1) { //player sprite is 68 pix wide
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	}
	case 3:
	{
		if ((grid[intPlayerY][intPlayerX - 1] == 0) || (grid[intPlayerY][intPlayerX - 1] == 7)) {

			if (player.getPosX() -hitPush<= intPlayerX + epsilon) {
				return true;
			}
			else {
				return false;
			}
			
		}else if ((grid[intPlayerY + 1][intPlayerX - 1] == 0 && (intPlayerY + 1) != y - 1) ||
			(grid[intPlayerY + 1][intPlayerX - 1] == 7 && (intPlayerY + 1) != y - 1)) {

			if (player.getPosX() - hitPush <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		break;
	}
	default:
		return false;
		break;
	}
}

void checkPlayerWall(Player& player, int exitX, int exitY, int direction, Enemy& enemy) {
	//std::cout << "key count: " << player.getKeyCount() << std::endl;

	//only changes made to player are x and y
	// can also reset map on level exit
	int intPlayerX = static_cast<int>(player.getPosX());
	int intPlayerY = static_cast<int>(player.getPosY());
	bool hitWall = false;
	bool hitCorner = false;
	player.setCanMove(true);

	switch (direction) {
	case 3:
		// left collision logic
		hitWall = (grid[intPlayerY][intPlayerX - 1] == 0) || (grid[intPlayerY][intPlayerX - 1] == 7);
		hitCorner = (grid[intPlayerY + 1][intPlayerX - 1] == 0 && (intPlayerY + 1) != y - 1) ||
			(grid[intPlayerY + 1][intPlayerX - 1] == 7 && (intPlayerY + 1) != y - 1);

		if (hitWall) { //if value zero; then cannot walk
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
		if (hitCorner) {
			//check if feet touch
			//std::cout << "intPlayerY + 1; " << intPlayerY + 1 << " getPosY: "<< getPosY() << " y: " << y << std::endl;
			if (player.getPosX() <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//std::cout << "feet touch" << std::endl;
				player.setPosX(intPlayerX + buffer);
				player.setCanMove(false);
			}
		}
		//check for exit
		if (player.getKeyCount() > 0) {
			if (grid[intPlayerY][intPlayerX - 1] == 4) {
				if (player.getPosX() <= intPlayerX + epsilon) {
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
			if (grid[intPlayerY + 1][intPlayerX - 1] == 4 && (intPlayerY + 1) != y - 1) {
				if (player.getPosX() <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
		}
		
		//check for key
		if (grid[intPlayerY][intPlayerX - 1] == 6) {
			if (player.getPosX() <= intPlayerX + epsilon) {
				//popGrid();
				grid[intPlayerY][intPlayerX - 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX - 1] == 6 && (intPlayerY + 1) != y - 1) {
			if (player.getPosX() <= intPlayerX + epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//popGrid();
				grid[intPlayerY + 1][intPlayerX - 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		break;
	case 1:
		// right logic
		hitWall = (grid[intPlayerY][intPlayerX + 1] == 0) || (grid[intPlayerY][intPlayerX + 1] == 7);
		hitCorner = (grid[intPlayerY + 1][intPlayerX + 1] == 0 && (intPlayerY + 1) != y - 1) ||
			(grid[intPlayerY + 1][intPlayerX + 1] == 7 && (intPlayerY + 1) != y - 1);

		if (hitWall) {
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
		if (hitCorner) {
			//check if feet touch
			//std::cout << "intPlayerY + 1; " << intPlayerY + 1 << " getPosY: "<< getPosY() << " y: " << y << std::endl;
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//std::cout << "feet touch" << std::endl;
				player.setPosX(intPlayerX + .52 - buffer);
				player.setCanMove(false);
			}
		}
		//check for exit
		if (player.getKeyCount() > 0) {
			if (grid[intPlayerY][intPlayerX + 1] == 4) {
				if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon) {//player sprite is 48 pix wide devided by 100 squareSize
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
			if (grid[intPlayerY + 1][intPlayerX + 1] == 4 && (intPlayerY + 1) != y - 1) {
				if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
		}
		//check for key
		if (grid[intPlayerY][intPlayerX + 1] == 6) {
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon) {//player sprite is 48 pix wide devided by 100 squareSize
				//popGrid();
				grid[intPlayerY][intPlayerX + 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX + 1] == 6 && (intPlayerY + 1) != y - 1) {
			if (player.getPosX() + .48 >= intPlayerX + 1 - epsilon && player.getPosY() + .68 >= intPlayerY + 1) {
				//popGrid();
				grid[intPlayerY + 1][intPlayerX + 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		break;
	case 0:
		// up logic
		hitWall = (grid[intPlayerY - 1][intPlayerX] == 0) || (grid[intPlayerY - 1][intPlayerX] == 7);
		hitCorner = (grid[intPlayerY - 1][intPlayerX + 1] == 0 && (intPlayerX + 1) != x - 1) ||
			(grid[intPlayerY - 1][intPlayerX + 1] == 7 && (intPlayerX + 1) != x - 1);

		if (hitWall) {
			//NOT legal move
			//std::cout << "not legal UP" << std::endl;
			if (player.getPosY() <= intPlayerY + epsilon) {
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + buffer);
				player.setCanMove(false);
			}
		}
		if (hitCorner) {
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
		if (player.getKeyCount() > 0) {
			if (grid[intPlayerY - 1][intPlayerX] == 4) {
				if (player.getPosY() <= intPlayerY + epsilon) {
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
			if (grid[intPlayerY - 1][intPlayerX + 1] == 4 && (intPlayerX + 1) != x - 1) {
				if (player.getPosY() <= intPlayerY + epsilon && player.getPosX() + .48 >= intPlayerX + 1) {
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
		}
		//check for key
		if (grid[intPlayerY - 1][intPlayerX] == 6) {
			if (player.getPosY() <= intPlayerY + epsilon) {
				//popGrid();
				grid[intPlayerY - 1][intPlayerX] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		if (grid[intPlayerY - 1][intPlayerX + 1] == 6 && (intPlayerX + 1) != x - 1) {
			if (player.getPosY() <= intPlayerY + epsilon && player.getPosX() + .48 >= intPlayerX + 1) {
				//popGrid();
				grid[intPlayerY - 1][intPlayerX + 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		break;
	case 2:
		// down logic
		hitWall = (grid[intPlayerY + 1][intPlayerX] == 0) || (grid[intPlayerY + 1][intPlayerX] == 7);
		hitCorner = (grid[intPlayerY + 1][intPlayerX + 1] == 0 && (intPlayerX + 1) != x - 1) || 
			(grid[intPlayerY + 1][intPlayerX + 1] == 7 && (intPlayerX + 1) != x - 1);
		if (hitWall) {
			//NOT legal move
			//std::cout << "not legal DOWN" << std::endl;
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
				//NOT LEGAL MOVE
				//std::cout << "NOT LEGAL LEFT" << std::endl;
				player.setPosY(intPlayerY + .32 - buffer);
				player.setCanMove(false);
			}
		}
		if (hitCorner) {
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
		if (player.getKeyCount() > 0) {

			if (grid[intPlayerY + 1][intPlayerX] == 4) {
				if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
			if (grid[intPlayerY + 1][intPlayerX + 1] == 4 && (intPlayerX + 1) != x - 1) {
				if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon && player.getPosX() + .48 >= intPlayerX + 1) { //player sprite is 68 pix wide
					//popGrid();
					player.setKeyCount(player.getKeyCount() - 1);
					startNewLevel(player, enemy);
				}
			}
		}
		//check for key
		if (grid[intPlayerY + 1][intPlayerX] == 6) {
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon) { //player sprite is 68 pix wide
				//popGrid();
				grid[intPlayerY + 1][intPlayerX] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		if (grid[intPlayerY + 1][intPlayerX + 1] == 6 && (intPlayerX + 1) != x - 1) {
			if (player.getPosY() + .68 >= intPlayerY + 1 - epsilon && player.getPosX() + .48 >= intPlayerX + 1) { //player sprite is 68 pix wide
				//popGrid();
				grid[intPlayerY + 1][intPlayerX + 1] = 1;
				player.getKeys().clear();
				player.setKeyCount(player.getKeyCount() + 1);
			}
		}
		break;
	default:
		player.setCanMove(false);
		break;
	}
}

void playerAndEnemyCheck(Player& player, Enemy& enemy, sf::Time deltaTime) {
	float pX = player.getPosX()*squareSize;
	float pY = player.getPosY() * squareSize;
	float pH = player.getSprite().getLocalBounds().height;
	float pW = player.getSprite().getLocalBounds().width;

	float eX,eY,eH,eW;

	for (auto it = enemy.getEnemies().begin(); it != enemy.getEnemies().end();) {
		eX = it->getPosX() * squareSize;
		eY = it->getPosY() * squareSize;
		eH = it->getHeightPx();
		eW = it->getWidthPx();

		if (pointInBox(pX, pY, pH, pW, eX, eY, eH, eW)) {
			player.getSprite().setColor(sf::Color::Red);
			if (!player.getIsHit()) {
				player.setHealth(player.getHealth() - 10);
				player.setIsHit(true);
			}
			player.setFlashTimer(0.15f); // flash for 150 ms
			
			float knockback;
			int playerDir = player.getDirection();
			int enemyDir = it->getDirection();
			int pushDir = enemyDir;

			// Reverse if both are moving in same direction
			if (player.getIsMoving() && playerDir == enemyDir) {
				pushDir = (playerDir + 2) % 4; // Reverse direction as well
			}
			else if (player.getIsMoving()) {
				pushDir = (playerDir + 2) % 4;
			}

			knockback = hitPush;

			float xOffset = 0, yOffset = 0;
			switch (pushDir) {
			case 0: yOffset = knockback*-1; break; // Up
			case 1: xOffset = knockback; break;  // Right
			case 2: yOffset = knockback; break;  // Down
			case 3: xOffset = knockback*-1; break; // Left
			}

			int intPlayerX = static_cast<int>(player.getPosX());
			int intPlayerY = static_cast<int>(player.getPosY());

			it->setPosX(it->getPosX() - xOffset);
			it->setPosY(it->getPosY() - yOffset);

			// Wall collision override
			if (hitWall(player, pushDir)) {
				//snap to wall
				if (pushDir == 0 || pushDir == 2) {
					player.setPosY(intPlayerY + ((pushDir == 0) ? 
						buffer: (1.0f - (player.getSprite().getLocalBounds().height / 100)) - buffer));
				}
				else {
					player.setPosX(intPlayerX + ((pushDir == 3) ? buffer : 
						(1.0f - (player.getSprite().getLocalBounds().width / 100)) - buffer));

				}
			}
			else {
				player.setPosX(player.getPosX() + xOffset);
				player.setPosY(player.getPosY() + yOffset);
			}
		}			
		++it;
	}

	if (player.getFlashTimer() > 0.0f) {
		player.setFlashTimer(player.getFlashTimer() - deltaTime.asSeconds());
		if (player.getFlashTimer() <= 0.0f) {
			player.getSprite().setColor(sf::Color::White); // reset tint
			player.setIsHit(false);
		}
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
					//std::cout << "dirx: " << dirX << " dirY: " << dirY << std::endl;
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
						bool hitEdge=grid[tempY][tempX - 1]==7 && it->getPosX() <= tempX + it->getEpsilon();
						bool hitWallCorner = !grid[tempY + 1][tempX - 1] && (tempY + 1) != y - 1 &&
							it->getPosX() <= tempX + it->getEpsilon() && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;
						bool hitEdgeCorner=grid[tempY + 1][tempX - 1]==7 && (tempY + 1) != y - 1 &&
							it->getPosX() <= tempX + it->getEpsilon() && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;
						
						if (hitWallSide || hitWallCorner|| hitEdge|| hitEdgeCorner) {
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
						bool hitEdge = grid[tempY][tempX + 1] ==7&& it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - it->getEpsilon();
						bool hitEdgeCorner = grid[tempY + 1][tempX + 1] ==7&& (tempY + 1) != y - 1 &&
							it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - it->getEpsilon() && it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;

						if (hitWallSide || hitWallCorner || hitEdge || hitEdgeCorner) {
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
						bool hitEdge = grid[tempY - 1][tempX] ==7&& it->getPosY() <= tempY + it->getEpsilon();
						bool hitEdgeCorner = grid[tempY - 1][tempX + 1] ==7&& (tempX + 1) != x - 1 &&
							it->getPosY() <= tempY + it->getEpsilon() && it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;


						if (hitWallSide || hitWallCorner || hitEdge || hitEdgeCorner) {
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
						bool hitEdge = grid[tempY + 2][tempX] ==7&& it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - it->getEpsilon();
						bool hitEdgeCorner = grid[tempY + 2][tempX + 1]==7 && (tempX + 1) != x - 1 &&
							it->getPosY() + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - it->getEpsilon() && it->getPosX() + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;

						if (hitWallSide || hitWallCorner || hitEdge || hitEdgeCorner) {
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
			if (tempX <= 0) {
				eraseFireball = true;
			}
			else {
				bool hitWall = (grid[tempY][tempX - 1] == 0 && it->getX() <= tempX + it->getEpsilon());
				bool hitCorner = (grid[tempY + 1][tempX - 1] == 0 && tempY + 1 != y - 1 &&
					it->getX() <= tempX + it->getEpsilon() && it->getY() + .64f >= tempY + 1);
				if (hitWall) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY][tempX - 1] = 2; //remove wall
					}
				}
				else if (hitCorner) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY + 1][tempX - 1] = 2; //remove wall
					}
				}
				else {
					it->setX(it->getX() + it->getSpeed());
				}
			}
			break;
		}
		case 1: { // RIGHT
			if (tempX >= grid[0].size() - 1) {
				eraseFireball = true;
			}
			else {
				bool hitWall = (grid[tempY][tempX + 1] == 0 && it->getX() + .645f >= tempX + 1 - it->getEpsilon());
				bool hitCorner = (grid[tempY + 1][tempX + 1] == 0 && tempY + 1 != y - 1 &&
					it->getX() + .645f >= tempX + 1 - it->getEpsilon() && it->getY() + .64f >= tempY + 1);
				if (hitWall) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY][tempX + 1] = 2;
					}
				}
				else if (hitCorner) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY + 1][tempX + 1] = 2;
					}
				}
				else {
					it->setX(it->getX() + it->getSpeed());
				}
			}
			break;
		}
		case 0: { // UP
			if (tempY <= 0) {
				eraseFireball = true;
			}
			else {
				bool hitWall = (grid[tempY - 1][tempX] == 0 && it->getY() <= tempY + it->getEpsilon());
				bool hitCorner = (grid[tempY - 1][tempX + 1] == 0 && tempX + 1 != x - 1 &&
					it->getY() <= tempY + it->getEpsilon() && it->getX() + .645f >= tempX + 1);
				if (hitWall) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY - 1][tempX] = 2;
					}
				}
				else if (hitCorner) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY - 1][tempX + 1] = 2;
					}
				}
				else {
					it->setY(it->getY() + it->getSpeed());
				}

			}
			break;
		}
		case 2: { // DOWN
			if (tempY + 1 >= grid.size() - 1) {
				eraseFireball = true;
			}
			else {
				bool hitWall = (grid[tempY + 1][tempX] == 0 && it->getY() + .64f >= tempY + 1 - it->getEpsilon());
				bool hitCorner = (grid[tempY + 1][tempX + 1] == 0 && tempX + 1 != x - 1 &&
					it->getY() + .64f >= tempY + 1 - it->getEpsilon() && it->getX() + .645f >= tempX + 1);
				if (hitWall) {
					eraseFireball = true;
					if (player.getSpell() == 2) {
						grid[tempY + 1][tempX] = 2;
					}
				}
				else if (hitCorner) {
					if (player.getSpell() == 2) {
						grid[tempY + 1][tempX + 1] = 2;
					}
				}
				else {
					it->setY(it->getY() + it->getSpeed());
				}
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
	playerAndEnemyCheck(player, enemy, deltaTime);
}