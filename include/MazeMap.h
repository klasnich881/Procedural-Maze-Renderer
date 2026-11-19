#pragma once
#include <vector>

struct GridPos {
    int x{};
    int y{};
};
class MazeMap{
    private:
        int mWidth{};
        int mHeight{};
        std::vector<int> mGrid;
        
        int toIndex(int x, int y) const;

        std::vector<GridPos> getUnvisitedNeighbors(const GridPos& current) const;

    public:
        //constructor
        MazeMap(int width, int height);

       void generateMaze();
       
       int getTile(int x, int y) const;

       void setTile(int x, int y, int value);

       bool isWall(int x, int y) const;

       int getWidth() const;

       int getHeight() const;

};