#pragma once
#include "player.h"
#include "enemies.h"
#include "collisionManager.h"
#include "render.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

class Renderer;

struct Menu {
	sf::RectangleShape menuWindow;
	sf::Text windowTitle;
	sf::Text windowText;
	sf::RectangleShape inputBox;
	sf::Text inputText;
	bool target;
};

struct Button {

	sf::Text btnText;
	sf::Texture btnTexture;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	bool active;
	bool hasSprite;
	bool visible;

	Button() = default;

	Button(const sf::Vector2f& size, const sf::Font& font, const std::string& text, bool click, float menuX, float menuY, int modX, int modY, bool viz) {
		rect.setSize(size);
		rect.setFillColor(sf::Color(100, 100, 250, 225));
		rect.setPosition(menuX + (20 * modX), menuY + 10 + (60 * modY));

		btnText.setFont(font);
		btnText.setString(text);
		btnText.setCharacterSize(18);
		btnText.setFillColor(sf::Color::White);
		btnText.setPosition(rect.getPosition().x + 5, rect.getPosition().y + 5);

		active = click;
		visible = viz;
	}
	sf::RectangleShape* getRect() { return &rect; }
	sf::Text* getText() { return &btnText; }
	sf::Sprite* getSprite() { return &sprite; }
	bool* getVisible() { return &visible; }

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

	//MAIN MENU
	sf::RectangleShape menuBorder;
	sf::Text title;
	Button resumeBtn;
	Button saveBtn;
	Button loadBtn;
	Button quitBtn;
	void updatePos(sf::Vector2f vec);

	//SAVE MENU
	Menu saveWindow;
	Button redFBB;
	Button blueFBB;
	Button saveFileBtn;
	Button saveCancelBtn;

	//HUD
	Menu statusBarMenu;
	sf::RectangleShape hpBar;
	sf::Vector2f hpBarSize;
	sf::RectangleShape manaBar;
	sf::Vector2f manaBarSize;
	Button equippedSpell;

	//
	sf::Vector2f windowSize;
	sf::Vector2f worldPos; //mouse position
	sf::Vector2f worldSize; //referencing game window
	sf::Vector2f positionMenu;
	sf::View view;
	sf::View uiView;

	void loadFile(Player& player, Enemy& enemies, GameState& gameState);
	void drawMenu(sf::RenderWindow& window, Player& player, GameState& gameState);
	void gameCheck(Player& player, int exitX, int exitY, int dir, Enemy& enemy, sf::Time deltaTime, 
		bool left, bool right, bool up, bool down, bool space, KeyManager& keyManager, sf::RenderWindow& window, Renderer& renderer);
	void drawGame(sf::RenderWindow& window, Player& player, Enemy& enemy, Renderer& renderer, GameState& gameState);
	std::vector<Button*>& getButtons() {
		return buttons;
	}
	std::vector<Button*>& getEquipment() {
		return equipment;
	}
	std::vector<Button*>& getSaveButtons() {
		return saveButtons;
	}
private:
	sf::Font font;

	void spawnBtn(sf::RenderWindow& window, Player& player, GameState& gameState);
	std::vector<Button*> buttons;
	std::vector<Button*> equipment;
	std::vector<Button*> saveButtons;
};


