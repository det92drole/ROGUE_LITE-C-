#include "debug.h"


std::ofstream logg("log.txt", std::ios::out | std::ios::trunc);  // Open the file once

void logMessage(const std::string& message) {
    if (logg.is_open()) {
        logg << message << std::endl;
    }
    else {
        std::cerr << "Failed to open log file!" << std::endl;
    }
}

//void testArr(std::vector<Enemy>& enemies) {
//    for (int i = 0; i < enemies.size(); i++) {
//        std::cout << "enemy: " << i << " POSx: " << enemies[i].getPosX() << " POSy: " << enemies[i].getPosY() << " height: " << enemies[i].getHeightPx() << std::endl;
//    }
//}