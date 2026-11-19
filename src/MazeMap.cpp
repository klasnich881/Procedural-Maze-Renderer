#include <algorithm>
#include <random>
#include <stack>
#include <utility>
#include <vector>
#include "MazeMap.h"

MazeMap::MazeMap(int width, int height) {
    // Make dimensions odd so outer walls and grid cells align
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;

    if (width < 5) width = 5;
    if (height < 5) height = 5;

    mWidth = width;
    mHeight = height;
    mGrid.assign(mWidth * mHeight, 1);
}

int MazeMap::toIndex(int x, int y) const {
    return y * mWidth + x;
}

int MazeMap::getTile(int x, int y) const {
    // Treat out of bounds/perimeter as solid wall
    if (x < 0 || x >= mWidth || y < 0 || y >= mHeight) {
        return 1;
    }
    return mGrid[toIndex(x, y)];
}

void MazeMap::setTile(int x, int y, int value) {
    if (x < 0 || x >= mWidth || y < 0 || y >= mHeight) {
        return;
    }
    mGrid[toIndex(x, y)] = value;
}

bool MazeMap::isWall(int x, int y) const {
    return getTile(x, y) == 1;
}

int MazeMap::getWidth() const {
    return mWidth;
}

int MazeMap::getHeight() const {
    return mHeight;
}

std::vector<GridPos> MazeMap::getUnvisitedNeighbors(const GridPos& current) const {
    std::vector<GridPos> candidates{};
    std::pair<int, int> directions[4] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};

    int i = 0;
    while (i < 4) {
        int newX = current.x + directions[i].first;
        int newY = current.y + directions[i].second;
        if ((newX > 0 && newX <= mWidth - 2) && (newY > 0 && newY <= mHeight - 2) && isWall(newX, newY)) {
            candidates.push_back({newX, newY});
        }
        i++;
    }
    return candidates;
}

void MazeMap::generateMaze() {
    // 1. Reset the entire grid back to solid walls (1)
    std::fill(mGrid.begin(), mGrid.end(), 1);

    // 2. Initialize Mersenne Twister RNG
    std::random_device rd;
    std::mt19937 rng(rd());

    // 3. Start carving at (1, 1)
    std::stack<GridPos> stack;
    setTile(1, 1, 0);
    stack.push({1, 1});

    // 4. Iterative DFS loop
    while (!stack.empty()) {
        GridPos current = stack.top();
        std::vector<GridPos> neighbors = getUnvisitedNeighbors(current);

        if (!neighbors.empty()) {
            // Pick a random unvisited neighbor 2 steps away
            std::uniform_int_distribution<size_t> dist(0, neighbors.size() - 1);
            GridPos next = neighbors[dist(rng)];

            // Carve the wall halfway between current and next
            int wallX = (current.x + next.x) / 2;
            int wallY = (current.y + next.y) / 2;
            setTile(wallX, wallY, 0);

            // Carve the neighbor cell itself and advance
            setTile(next.x, next.y, 0);
            stack.push(next);
        } else {
            // Dead end: backtrack
            stack.pop();
        }
    }
}