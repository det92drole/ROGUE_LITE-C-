#include "enemies.h"

Enemy::Enemy()
	: id(-1), frame(0), frameTime(0.2f), elapsedTime(0.0f),
	enemyPosX(0.0f), enemyPosY(0.0f), enemyHealth(100),
	direction(0), speed(0.5f), epsilon(0.2f),
	widthPx(0), heightPx(0)
{
	// sprite doesn't need init unless assigning texture here
}

std::vector<std::shared_ptr<sf::Texture>> Enemy::textures;

std::pair<int, int> randPos(const std::vector<std::vector<int>>& grid) {
	std::vector<std::pair<int, int>> spawnsEnemy;

	int rows = grid.size();
	int cols = grid[0].size();

	// Only loop through cells with full valid neighbors
	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (
				grid[i][j] == 1 &&
				grid[i + 1][j] == 1 && grid[i - 1][j] == 1 &&
				grid[i][j + 1] == 1 && grid[i][j - 1] == 1 &&
				grid[i - 1][j - 1] == 1 && grid[i - 1][j + 1] == 1 &&
				grid[i + 1][j + 1] == 1 && grid[i + 1][j - 1] == 1
				) {
				spawnsEnemy.emplace_back(i, j);
			}
		}
	}

	if (!spawnsEnemy.empty()) {
		return spawnsEnemy[std::rand() % spawnsEnemy.size()];
	}
	else {
		std::cerr << "[randPos] No valid spawn points found!\n";
		return { -1, -1 };
	}
}

std::vector<Enemy>& Enemy::getEnemies() {
	static std::vector<Enemy> enemyArr;
		return enemyArr;
}

void Enemy::update(sf::Time deltaTime) {
	//updated sprite animation
	for (auto it = getEnemies().begin(); it != getEnemies().end(); ) {
		it->elapsedTime += deltaTime.asSeconds();
		if (it->elapsedTime >= it->frameTime) {
			it->frame = (it->frame + 1) % 8;
			it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));
			it->elapsedTime = 0.0f;
		}
		++it;
	}
}

//START REFERENCE: enemy collision used to be in .update()
/*
void Enemy::update(sf::Time deltaTime) {
	//std::cout << "array size check 2: " <<getEnemies().size()<< std::endl;
	for (auto it = getEnemies().begin(); it != getEnemies().end(); ) {
		it->elapsedTime += deltaTime.asSeconds();

		////COUT
		//std::cout << "{" << std::endl;
		//std::cout << "Enemy id#: " << it->id << std::endl;
		//std::cout << "posX: " << it->enemyPosX << " posY: " << it->enemyPosY << std::endl;
		//std::cout << "widthPx: " << it->getWidthPx() << " heightPx: " << it->getHeightPx() << std::endl;

		//std::cout << "frames: " << it->frame << std::endl;
		//std::cout << "frameTime: " << it->frameTime << std::endl;
		//std::cout << "}" << std::endl;
		////COUT END

		if (it->elapsedTime >= it->frameTime) {
			it->frame = (it->frame + 1) % 8;
			it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));
			it->elapsedTime = 0.0f;
		}

		/*
		int tempX = static_cast<int>(it->enemyPosX);
		int tempY = static_cast<int>(it->enemyPosY);
		//std::cout << "enemyX: " << it->enemyPosX << " enemyY: " << it->enemyPosY << std::endl;
		//logg << "{ " << std::endl;
		//logg << "enemyX: " << it->enemyPosX << " enemyY: " << it->enemyPosY << std::endl;
		//logg << "tempX: " << tempX << " tempY: " << tempY << std::endl;

		//logg << "Direction: " << it->direction << std::endl;
		switch (it->direction) {
		case 3: {
			// only left true
			it->enemyPosX += it->speed * deltaTime.asSeconds();

			if (tempX <= 0) {
				it->speed *= -1;
				//logg << "Speed after: " << it->speed << std::endl;
				it->direction = 1;
			}
			else {
				bool hitWallSide = !grid[tempY][tempX - 1] && it->enemyPosX <= tempX + epsilon;
				bool hitWallCorner = !grid[tempY + 1][tempX - 1] && (tempY + 1) != y - 1 &&
					it->enemyPosX <= tempX + epsilon && it->enemyPosY + static_cast<float>(getHeightPx() / 100.0f) >= tempY + 1;
				if (hitWallSide || hitWallCorner) {
					//logg << "hit" << "enemyX: " << it->enemyPosX << " enemyY: " << it->enemyPosY << std::endl;
					//logg << "wall val: " << grid[tempY][tempX - 1] << std::endl;
					//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
					//logg << "Speed before: " << it->speed << std::endl;
					it->speed *= -1;
					//logg << "Speed after: " << it->speed << std::endl;
					it->direction = 1;
				}
			}

			//logg << "}" << std::endl;
			//logg << std::endl;
			break;
		}
		case 1: {
			// only right true
			it->enemyPosX += it->speed * deltaTime.asSeconds();
			if (tempX >= grid[0].size()-1) {
				it->speed *= -1;
				//logg << "Speed after: " << it->speed << std::endl;
				it->direction = 3;
			}
			else {
				bool hitWallSide = !grid[tempY][tempX + 1] && it->enemyPosX + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - epsilon;
				bool hitWallCorner = !grid[tempY + 1][tempX + 1] && (tempY + 1) != y - 1 &&
					it->enemyPosX + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1 - epsilon && it->enemyPosY + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 1;

				if (hitWallSide || hitWallCorner) {
					//logg << "hit" << std::endl;
					//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
					//logg << "Speed before: " << it->speed << std::endl;
					it->speed *= -1;
					//logg << "Speed after: " << it->speed << std::endl;
					it->direction = 3;
				}
			}
			break;
		}
		case 0: {
			// only up true
			it->enemyPosY += it->speed * deltaTime.asSeconds();

			if (tempY <= 0) {
				it->speed *= -1;
				//logg << "Speed after: " << it->speed << std::endl;
				it->direction = 2;
			}
			else {
				bool hitWallSide = !grid[tempY - 1][tempX] && it->enemyPosY <= tempY + epsilon;
				bool hitWallCorner = !grid[tempY - 1][tempX + 1] && (tempX + 1) != x - 1 &&
					it->enemyPosY <= tempY + epsilon && it->enemyPosX + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;

				if (hitWallSide || hitWallCorner) {
					//logg << "hit" << std::endl;
					//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
					//logg << "Speed before: " << it->speed << std::endl;
					it->speed *= -1;
					//logg << "Speed after: " << it->speed << std::endl;
					it->direction = 2;
				}
			}
			break;
		}
		case 2: {
			// only down true
			it->enemyPosY += it->speed * deltaTime.asSeconds();

			if (tempY >= grid.size()-1) {
				it->speed *= -1;
				//logg << "Speed after: " << it->speed << std::endl;
				it->direction = 0;
			}
			else {
				bool hitWallSide = !grid[tempY + 2][tempX] && it->enemyPosY + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - epsilon;
				bool hitWallCorner = !grid[tempY + 2][tempX + 1] && (tempX + 1) != x - 1 &&
					it->enemyPosY + static_cast<float>(it->getHeightPx() / 100.0f) >= tempY + 2 - epsilon && it->enemyPosX + static_cast<float>(it->getWidthPx() / 100.0f) >= tempX + 1;

				if (hitWallSide || hitWallCorner) {
					//logg << "hit" << std::endl;
					//logg << "Side: " << hitWallSide << ", Corner: " << hitWallCorner << std::endl;
					//logg << "Speed before: " << it->speed << std::endl;
					it->speed *= -1;
					//logg << "Speed after: " << it->speed << std::endl;
					it->direction = 0;
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
*/
//END REFERENCE


void Enemy::draw(sf::RenderWindow& window) {

	float outlineThickness = 2.f;

	for (auto it = getEnemies().begin(); it != getEnemies().end(); ++it) {
		
		////COUT
		//std::cout << "{" << std::endl;
		//std::cout << "Enemy id#: " << it->id << std::endl;
		//std::cout << "posX: " << it->enemyPosX << " posY: " << it->enemyPosY << std::endl;
		//std::cout << "widthPx: " << it->getWidthPx() << " heightPx: " << it->getHeightPx() << std::endl;
		//std::cout << "frames: " << it->frame << std::endl;
		//std::cout << "frameTime: " << it->frameTime << std::endl;
		//std::cout << "}" << std::endl;
		////COUT END
		

		if (it->sprite.getTexture() == nullptr) {
			std::cerr << "Warning: sprite has no texture!" << std::endl;
		}
		it->sprite.setPosition(it->enemyPosX * squareSize, it->enemyPosY * squareSize);
		it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));

		window.draw(it->sprite);

		//sf::FloatRect bounds = it->sprite.getGlobalBounds(); // Get sprite's bounds
		//sf::RectangleShape border;
		//border.setSize(sf::Vector2f(bounds.width - outlineThickness, bounds.height - outlineThickness));
		//border.setPosition(bounds.left + outlineThickness / 2.f, bounds.top + outlineThickness / 2.f);
		//border.setFillColor(sf::Color::Transparent); // No fill
		//border.setOutlineColor(sf::Color::Red);      // Border color
		//border.setOutlineThickness(2.f);             // Border thickness
		//window.draw(border);
		//std::cout << "width: " << bounds.width << " height: " << bounds.height << std::endl;
	}
}

void Enemy::spawnEnemies() {
	
	int enemyRand = std::rand() % 3;

	Enemy::textures.clear();

	if (Enemy::textures.empty()) {
		for (int i = 0; i < 3; ++i) {
			auto tex = std::make_shared<sf::Texture>();
			std::string path = "Assets/Enemies/" + std::bitset<4>(i).to_string() + ".png";

			if (!tex->loadFromFile(path)) {
				std::cerr << "Failed to load enemy texture at " << path << std::endl;
			}
			else {
				Enemy::textures.emplace_back(tex);
			}
		}
	}
	
	Enemy::getEnemies().clear();

	while (Enemy::getEnemies().size() < 10) {
		auto [y, x] = randPos(grid);
		if (x < 0 || y < 0) continue;

		Enemy enemy;
		enemy.id = Enemy::getEnemies().size();
		enemy.enemyPosX = x;
		enemy.enemyPosY = y;
		enemy.direction = std::rand() % 4;
		enemy.frame = std::rand() % 8;

		switch (enemyRand) {
			case 0: {
				//brain
				enemy.setWidthPx(60);
				enemy.setHeightPx(102);
				break;
			}
			case 1: {
				//red
				enemy.setWidthPx(78);
				enemy.setHeightPx(105);
				break;
			}
			case 2: {
				//tusk
				enemy.setWidthPx(66);
				enemy.setHeightPx(84);
				break;
			}
		}

		if (enemyRand < Enemy::textures.size()) {
			enemy.sprite.setTexture(*Enemy::textures[enemyRand]);
		}

		enemy.sprite.setPosition(x * squareSize, y * squareSize);
		enemy.sprite.setTextureRect(sf::IntRect(enemy.frame * enemy.getWidthPx(), 0, enemy.getWidthPx(), enemy.getHeightPx()));

		if (enemy.direction == 0 || enemy.direction == 3) {
			enemy.speed *= -1;
		}

		Enemy::getEnemies().emplace_back(enemy);
	}

	if (getEnemies().size() < 50) {
		std::cerr << "Warning: Only spawned " << getEnemies().size() << std::endl;
	}
}



int Enemy::getHealth() const {
	return enemyHealth;
}

void Enemy::setHealth(int health) {
	enemyHealth = health;
}

void Enemy::changeXY(float x, float y) {
	enemyPosY = y;
	enemyPosX = x;
	//std::cout << "CHANGED POS X&Y VALUE" << std::endl;
}