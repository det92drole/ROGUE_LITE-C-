#include "rand.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

int y = 30;
int x = 15;
int generations = 10;
int pathProb = 63;
int spawnFloatX = 0;
int spawnFloatY = 0;
int exitX=0;
int exitY=0;
int keyX = 0;
int keyY = 0;

//0 is wall(#), 1 is path(.), 2 is path touching wall(,), 3 is path/player-spawn(@);
// grid[row][col] => grid[y][x]
std::vector<std::vector<int>> grid(y, std::vector<int>(x, 0));
std::vector<int> spawns;
std::vector<int> exits;


int randIndex() {
    return std::rand() % 100; //
}

int near(int x, int y) {
    int count = 0;
    for (int h = y - 1; h < 2 + y; h++) {
        for (int w = x - 1; w < 2 + x; w++) {
            if (!(w == x && h == y)) {
                count += grid[h][w];
                //std::cout << map[h][w];
            }
            else {
                //std::cout << ".";
            }
        }
        //std::cout << std::endl;
    }
    //std::cout << count << std::endl;
    return count;
}

bool isPathAvailable(const std::vector<std::vector<int>>& grid, int startX, int startY, int endX, int endY) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Bounds + wall check
    if (grid[startY][startX] == 0 || grid[endY][endX] == 0)
        return false;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> q;

    // Start BFS
    q.push({ startX, startY });
    visited[startY][startX] = true;

    const std::vector<std::pair<int, int>> directions = {
        {0, -1},  // Up
        {1, 0},   // Right
        {0, 1},   // Down
        {-1, 0}   // Left
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == endX && y == endY)
            return true;

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && ny >= 0 && nx < cols && ny < rows &&
                !visited[ny][nx] && grid[ny][nx] != 0 && grid[ny][nx] != 7) {
                visited[ny][nx] = true;
                q.push({ nx, ny });
            }
        }
    }

    return false; // No path found
}

void runWorm(int xS, int yS) {

    //worm path
    std::vector<int> validDirections;

    // Check which directions are valid
    if (yS >= 2 && grid[yS-1][xS]!=5) validDirections.push_back(0);  // Up
    if (xS <= (x - 3)&& grid[yS][xS+1] != 5) validDirections.push_back(1);  // Right
    // if (yS <= (y - 3)) validDirections.push_back(2);  // Down; not valid direction
    if (xS >= 2 && grid[yS][xS-1] != 5) validDirections.push_back(3);  // Left

    if (validDirections.empty()) {
        //std::cout << "No valid moves. Stopping worm." << std::endl;
        return;  // Stop recursion if no moves are available
    }

    int direction = validDirections[rand() % validDirections.size()];

    switch (direction) {
    case 0:  // Move Up
        //std::cout << "Move Up @" << x << "," << y << std::endl;
        --yS;
        break;
    case 1:  // Move Right
        //std::cout << "Move Right @" << x << "," << y << std::endl;
        ++xS;
        break;
    //case 2:  // Move Down
        //std::cout << "DONT Move Down @" << x << "," << y << std::endl;
        //++yS;
        //break;
    case 3:  // Move Left
        //std::cout << "Move Left @" << x << "," << y << std::endl;
        //should never be called
        --xS;
        break;
    }

    // **Only recurse if we haven't hit the end**
    if (yS >2) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (grid[yS+i][xS+j]==0) {
                    grid[yS + i][xS + j] = 2;
                }
            }
        }
        grid[yS][xS] = 5;  // Place path tile
        runWorm(xS, yS);
    }
    else {
        //std::cout << "Reached near top of grid. Stopping worm." << std::endl;
        grid[exitY][exitX] = 2; //replace original exit with walkable path
        //change exit point to worm end
        exitX = xS;
        exitY = yS;
        grid[exitY][exitX] = 4;
        return;
    }
}

void playerSpawnCheck() {
    //find a spawn point for player
    for (int i = 0; i < x; i++) {
        if (grid[y - 3][i] == 1) { //if tile above bottom row is path not adjacent to wall; then can be a spawn point
            spawns.push_back(i);
        }
    }
    if (!spawns.empty()) {
        spawnFloatX = spawns[std::rand() % spawns.size()];
        spawnFloatY = y - 3;
        grid[spawnFloatY][spawnFloatX] = 3;
        //check passed on exit AND spawn
        //check for clear path from spawn to exit
        if (!isPathAvailable(grid, spawnFloatX, spawnFloatY, exitX, exitY)) {
            runWorm(spawnFloatX, spawnFloatY); // Try to create a path

            if (!isPathAvailable(grid, spawnFloatX, spawnFloatY, exitX, exitY)) {
                popGrid(); // Give up, try fresh map
            }
        }
        grid[spawnFloatY][spawnFloatX] = 3; //redeclare since runWorm changes spawn tile value
        //find key spawn
        std::vector<std::pair<int, int>> keySpawns;

        for (int h = 1; h < y - 1; h++) {
            for (int w = 1; w < x - 1; w++) {
                if (grid[h][w] == 1) {
                    keySpawns.emplace_back(h, w);
                }
            }
        }
        //randomly select a path tile for key
        if (!keySpawns.empty()) {
            std::pair<int, int> keySpawn = keySpawns[rand() % keySpawns.size()];
            grid[keySpawn.first][keySpawn.second] = 6;
            keyX=keySpawn.second;
            keyY=keySpawn.first;
        }
        
    }
    else {
        // Handle this somehow -- maybe log an error or fallback
        std::cout << "No valid spawn points found! Generating new grid." << std::endl;
        //rerun popGrid();
        popGrid(); //re-pop grid
    }
}

void cleanGrid() {
    for (int gen = 0; gen < generations; gen++) {
        for (int h = 1; h < y - 1; h++) {
            for (int w = 1; w < x - 1; w++) {
                int count = near(w, h);
                if (grid[h][w] == 0 && count >= 6) grid[h][w] = 1;
                if (grid[h][w] == 1 && count <= 3) grid[h][w] = 0;
            }
        }
        //printGrid();
        //std::cout << std::endl;
    }

    //make edges of map walls
    for (int i = 0; i < y; i++) {
        grid[i][0] = 7;
        grid[i][x - 1] = 7;

    }
    //make edges of map walls
    for (int i = 0; i < x; i++) {
        grid[0][i] = 7;
        grid[y - 1][i] = 7;
    }

    //add "," for path spaces that are adjacent to walls
    for (int h = 1; h < y - 1; h++) {
        for (int w = 1; w < x - 1; w++) {
            if (grid[h][w] == 1) {
                if (!grid[h + 1][w] || !grid[h - 1][w] || !grid[h][w + 1] || !grid[h][w - 1]) {
                    grid[h][w] = 2;
                }
            }
        }
    }

    //find exit
    for (int i = 0; i < x; i++) {
        if (grid[2][i] == 1) { //if tile below top row is path not adjacent to wall; then can be a exit point
            exits.push_back(i);
        }
    }
    if (!exits.empty()) {
        exitX = exits[std::rand() % exits.size()];
        exitY = 2;
        grid[exitY][exitX] = 4;
        //once exit confirmed, check for player spawn
        playerSpawnCheck();
    }
    else {
        // Handle this somehow -- maybe log an error or fallback
        std::cout << "No valid exit points found! Generating new grid." << std::endl;
        //rerun popGrid();
        grid.clear(); //empty 
        grid = std::vector<std::vector<int>>(y, std::vector<int>(x, 0)); //reset size
        popGrid(); //re-pop grid
    }
}

void popGrid() {
    grid.clear(); //empty 
    grid = std::vector<std::vector<int>>(y, std::vector<int>(x, 0)); //reset size

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            grid[i][j] = 1; 
            if (randIndex() > pathProb) {
                grid[i][j] = 0;
            }
        }
    }
    cleanGrid();
}

void printGrid() {

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (grid[i][j] == 2) {
                std::cout << ","; //path touching wall
            }
            if (grid[i][j]==0) {
                std::cout << "#"; //wall
            }
            if(grid[i][j] == 1) {
                std::cout << "."; //path
            }
            if (grid[i][j] == 3) {
                std::cout << "@"; //player spawn
            }
            if (grid[i][j] == 4) {
                std::cout << "$"; //exit
            }
            if (grid[i][j] == 5) {
                std::cout << "*"; //worm path
            }
            if (grid[i][j] == 6) {
                std::cout << "!"; //item/key
            }
            if (grid[i][j] == 7) {
                std::cout << "%"; //edge wall
            }
        }
        std::cout << "\n";
    }
}