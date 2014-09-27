#pragma once

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;

class GameOfLife
{
public:
    typedef pair<int, int> Cell;

    virtual const vector<Cell> & getLiveCells() = 0;
    virtual vector<Cell> findAdjacentNeighbours(Cell, Cell) = 0;
    virtual bool isLiveCell(int x, int y) = 0;
    virtual void addLiveCell(int x, int y) = 0;
    virtual void tick() = 0;
    virtual void reset() = 0;
    virtual ~GameOfLife() {};

    static string to_string(Cell cell)
    {
        return string("(" + std::to_string(cell.first) + ", " + std::to_string(cell.second) + ")");
    }
};
