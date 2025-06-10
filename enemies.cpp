#include "enemies.h"

Enemy::Enemy()
	: id(-1), frame(0), frameTime(0.2f), elapsedTime(0.0f),
	enemyPosX(0.0f), enemyPosY(0.0f), enemyHealth(100),
	direction(0), speed(0.5f), epsilon(0.2f),
	widthPx(0), heightPx(0), agro(false)
{
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

	if (Enemy::texturesBoss.empty()) {
		for (int i = 0; i < 1; ++i) { //hard coded val
			auto tex = std::make_shared<sf::Texture>();
			std::string path = "Assets/Boss/" + std::bitset<4>(i).to_string() + ".png";

			if (!tex->loadFromFile(path)) {
				std::cerr << "Failed to load enemy texture at " << path << std::endl;
			}
			else {
				Enemy::texturesBoss.emplace_back(tex);
			}
		}
	}
}

std::vector<std::shared_ptr<sf::Texture>> Enemy::textures;
std::vector<std::shared_ptr<sf::Texture>> Enemy::texturesBoss;

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

std::vector<Enemy>& Enemy::getBoss() {
	static std::vector<Enemy> bossArr;
	return bossArr;
}

void Enemy::merge() {
	mergeArr.clear();

	// Push pointers to the enemies
	for (auto& e : getEnemies()) {
		mergeArr.push_back(&e);
	}

	// Push pointers to the bosses
	for (auto& b : getBoss()) {
		mergeArr.push_back(&b);
	}
}

std::vector<std::shared_ptr<sf::Texture>>& Enemy::getTextures() {
	return textures;
}

std::vector<std::shared_ptr<sf::Texture>>& Enemy::getBossTextures() {
	return texturesBoss;
}

void Enemy::bossMech() {
	//boss.prevX = static_cast<int>(getBoss()[0].getPosX());
	//getBoss()[0].prevY = static_cast<int>(getBoss()[0].getPosY());
	Enemy& boss = getBoss()[0];

	if (!boss.agro) {
		switch (boss.getDirection()) {
		case 0:
		{
			if (boss.getPrevY() - 2 > boss.getPosY()) {
				boss.setPrevY(static_cast<int>(boss.getPosY()));
				boss.setDirection(std::rand() % 4);
				if (boss.getDirection() == 0 || boss.getDirection() == 3) {
					boss.setSpeed(std::abs(boss.getSpeed()) * -1);
				}
				else {
					boss.setSpeed(std::abs(boss.getSpeed()));
				}
			}
			break;
		}
		case 1:
		{
			if (boss.getPrevX() + 2 < boss.getPosX()) {
				boss.setPrevX(static_cast<int>(boss.getPosX()));
				boss.setDirection(std::rand() % 4);
				if (boss.getDirection() == 0 || boss.getDirection() == 3) {
					boss.setSpeed(std::abs(boss.getSpeed()) * -1);
				}
				else {
					boss.setSpeed(std::abs(boss.getSpeed()));
				}
			}
			break;
		}
		case 2:
		{
			if (boss.getPrevY() + 2 < boss.getPosY()) {
				boss.setPrevY(static_cast<int>(boss.getPosY()));
				boss.setDirection(std::rand() % 4);
				if (boss.getDirection() == 0 || boss.getDirection() == 3) {
					boss.setSpeed(std::abs(boss.getSpeed()) * -1);
				}
				else {
					boss.setSpeed(std::abs(boss.getSpeed()));
				}
			}
			break;
		}
		case 3:
		{
			if (boss.getPrevX() - 2 > boss.getPosX()) {
				boss.setPrevX(static_cast<int>(boss.getPosX()));
				boss.setDirection(std::rand() % 4);
				if (boss.getDirection() == 0 || boss.getDirection() == 3) {
					boss.setSpeed(std::abs(boss.getSpeed()) * -1);
				}
				else {
					boss.setSpeed(std::abs(boss.getSpeed()));
				}
			}
			break;
		}
		}
	}
}

void Enemy::update(sf::Time deltaTime) {
	//updated sprite animation
	int agroMod = 1;

	for (auto it = getEnemies().begin(); it != getEnemies().end(); ) {
		if (it->getAgro()) {
			agroMod = 2;
		}
		it->elapsedTime += deltaTime.asSeconds()*agroMod;
		if (it->elapsedTime >= it->frameTime) {
			it->frame = (it->frame + 1) % 8;
			it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));
			it->elapsedTime = 0.0f;
		}
		++it;
	}
	for (auto it = getBoss().begin(); it != getBoss().end(); ) {
		it->elapsedTime += deltaTime.asSeconds() * agroMod;
		if (it->elapsedTime >= it->frameTime) {
			it->frame = (it->frame + 1) % 10;
			it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));
			it->elapsedTime = 0.0f;
		}
		++it;
	}
	bossMech();
}

void Enemy::draw(sf::RenderWindow& window) {

	for (auto it = getEnemies().begin(); it != getEnemies().end(); ++it) {

		if (it->sprite.getTexture() == nullptr) {
			std::cerr << "Warning: sprite has no texture!" << std::endl;
		}
		it->sprite.setPosition(it->enemyPosX * squareSize, it->enemyPosY * squareSize);
		it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));

		window.draw(it->sprite);
	}
	for (auto it = getBoss().begin(); it != getBoss().end(); ++it) {

		if (it->sprite.getTexture() == nullptr) {
			std::cerr << "Warning: sprite has no texture!" << std::endl;
		}
		it->sprite.setPosition(it->enemyPosX * squareSize, it->enemyPosY * squareSize);
		it->sprite.setTextureRect(sf::IntRect(it->frame * it->getWidthPx(), 0, it->getWidthPx(), it->getHeightPx()));

		window.draw(it->sprite);
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
		enemy.agro = false;
		enemy.setTextSelect(enemyRand);
		enemy.prevX = static_cast<int>(enemy.enemyPosX);
		enemy.prevY = static_cast<int>(enemy.enemyPosY);


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
		//std::cerr << "Warning: Only spawned " << getEnemies().size() << std::endl;
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

void Enemy::bossSpawn(int exitX, int exitY) {
	int bossRand = std::rand() % 1; //hard coded val

	Enemy::texturesBoss.clear();

	if (Enemy::texturesBoss.empty()) {
		for (int i = 0; i < 1; ++i) { //hard coded val
			auto tex = std::make_shared<sf::Texture>();
			std::string path = "Assets/Boss/" + std::bitset<4>(i).to_string() + ".png";

			if (!tex->loadFromFile(path)) {
				std::cerr << "Failed to load enemy texture at " << path << std::endl;
			}
			else {
				Enemy::texturesBoss.emplace_back(tex);
			}
		}
	}

	Enemy enemy;
	enemy.id = -1;
	enemy.enemyPosX = exitX;
	enemy.enemyPosY = exitY;
	enemy.direction = std::rand() % 4;
	enemy.agro = false;
	enemy.setBossTexture(bossRand);
	enemy.prevX = exitX;
	enemy.prevY = exitY;

	switch (bossRand) {
	case 0: {
		//0000.png STONE 144*159 10frames
		enemy.setWidthPx(144);
		enemy.setHeightPx(159);
		enemy.frame = std::rand() % 10;

		break;
	}
	}

	if (bossRand < Enemy::texturesBoss.size()) {
		enemy.sprite.setTexture(*Enemy::texturesBoss[bossRand]);
	}

	enemy.sprite.setPosition(enemy.enemyPosX * squareSize, enemy.enemyPosY * squareSize);
	enemy.sprite.setTextureRect(sf::IntRect(enemy.frame * enemy.getWidthPx(), 0, enemy.getWidthPx(), enemy.getHeightPx()));

	if (enemy.direction == 0 || enemy.direction == 3) {
		enemy.speed *= -1;
	}

	Enemy::getBoss().emplace_back(enemy);

}